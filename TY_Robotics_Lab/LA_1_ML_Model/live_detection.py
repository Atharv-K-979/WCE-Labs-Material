import sys
import time
import os
from collections import deque
import cv2
import torch
import torch.nn as nn
from torchvision import transforms, models
from PIL import Image

# 1. Verify Model Path
MODEL_PATH = 'human_detector.pth'
if not os.path.exists(MODEL_PATH):
    print(f"Error: '{MODEL_PATH}' not found. Please run train.py first!")
    sys.exit(1)

# 2. Rebuild Model Structure & Load Fine-Tuned Weights
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
print(f"Using device: {device}")

model = models.mobilenet_v2(weights=None)
model.classifier[1] = nn.Sequential(
    nn.Dropout(p=0.2),
    nn.Linear(model.last_channel, 2)
)
model.load_state_dict(torch.load(MODEL_PATH, map_location=device, weights_only=True))
model.to(device)
model.eval()

# 3. Load Multi-Pose Cascades (Frontal + Tilt + Profile Left/Right + Upper Body)
frontal_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_alt2.xml')
profile_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_profileface.xml')
upperbody_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_upperbody.xml')

# 4. Preprocessing Transformations
transform = transforms.Compose([
    transforms.Resize((224, 224)),
    transforms.ToTensor(),
    transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])
])

classes = ['human', 'non_human']

# 5. Connect to Camera (DirectShow for Windows stability)
def get_camera():
    for index in [0, 1, 2]:
        cap = cv2.VideoCapture(index, cv2.CAP_DSHOW)
        if cap.isOpened():
            ret, _ = cap.read()
            if ret:
                print(f"Connected to Camera (Index {index})")
                return cap
            cap.release()
        cap = cv2.VideoCapture(index)
        if cap.isOpened():
            ret, _ = cap.read()
            if ret:
                print(f"Connected to Camera (Index {index}) via default backend")
                return cap
            cap.release()
    return None

cap = get_camera()
if cap is None:
    print("Error: Could not open camera. Please check camera connections.")
    sys.exit(1)

print("\n" + "="*65)
print("     AI INTERVIEW PRESENCE MONITOR (MULTI-POSE TRACKING)")
print("="*65)
print(" Features:")
print(" - Multi-Angle Head & Neck Movement Tracking (Front, Tilt, Left/Right)")
print(" - Upper Body & Shoulder Verification")
print(" - Absence Grace Filter (Prevents False NO During Natural Movements)")
print(" Press 'q' in the camera window to quit.\n")

# Settings & States
ABSENCE_GRACE_FRAMES = 20  # ~0.7-1.0s grace window before declaring candidate absent
frames_without_detection = 0
prev_presence = None
start_time = time.time()
prev_time = time.time()

while True:
    ret, frame = cap.read()
    if not ret:
        time.sleep(0.04)
        continue

    h, w, _ = frame.shape
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    detected_boxes = []
    detection_type = "None"

    # Step 1: Frontal & Tilted Face Detection (alt2 is highly tolerant to head tilt)
    frontal_faces = frontal_cascade.detectMultiScale(
        gray, scaleFactor=1.12, minNeighbors=4, minSize=(50, 50)
    )
    if len(frontal_faces) > 0:
        detected_boxes.extend(frontal_faces)
        detection_type = "Face (Frontal/Tilt)"

    # Step 2: If head turned, check Left Profile
    if len(detected_boxes) == 0:
        left_profiles = profile_cascade.detectMultiScale(
            gray, scaleFactor=1.12, minNeighbors=4, minSize=(50, 50)
        )
        if len(left_profiles) > 0:
            detected_boxes.extend(left_profiles)
            detection_type = "Face (Profile Left)"

    # Step 3: If head turned other way, check Right Profile (flipped gray)
    if len(detected_boxes) == 0:
        flipped_gray = cv2.flip(gray, 1)
        right_profiles = profile_cascade.detectMultiScale(
            flipped_gray, scaleFactor=1.12, minNeighbors=4, minSize=(50, 50)
        )
        if len(right_profiles) > 0:
            for (fx, fy, fw, fh) in right_profiles:
                # Map flipped coordinates back to original frame
                orig_x = w - fx - fw
                detected_boxes.append((orig_x, fy, fw, fh))
            detection_type = "Face (Profile Right)"

    # Step 4: If looking down / neck moved down, check Upper Body / Torso
    if len(detected_boxes) == 0:
        upper_bodies = upperbody_cascade.detectMultiScale(
            gray, scaleFactor=1.15, minNeighbors=3, minSize=(80, 80)
        )
        if len(upper_bodies) > 0:
            detected_boxes.extend(upper_bodies)
            detection_type = "Upper Body / Torso"

    # Step 5: Neural Network Forward Pass
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    pil_img = Image.fromarray(rgb_frame)
    input_tensor = transform(pil_img).unsqueeze(0).to(device)

    with torch.no_grad():
        outputs = model(input_tensor)
        probabilities = torch.softmax(outputs, dim=1)[0]
        human_prob = probabilities[0].item()

    # Step 6: Fusion & Absence Filter Logic
    physical_cue_found = (len(detected_boxes) > 0)
    
    # Raw instant detection
    if physical_cue_found:
        instant_detected = True
        conf_percent = max(human_prob * 100.0, 94.0)
    elif human_prob >= 0.70:
        instant_detected = True
        conf_percent = human_prob * 100.0
        detection_type = "Deep Neural Feature"
    else:
        instant_detected = False
        conf_percent = (1.0 - human_prob) * 100.0

    # Apply Absence Grace Filter
    if instant_detected:
        frames_without_detection = 0
        is_present = True
    else:
        frames_without_detection += 1
        if frames_without_detection >= ABSENCE_GRACE_FRAMES:
            is_present = False
        else:
            # Within grace period during head turning
            is_present = True

    # Console Logging on Transition
    if is_present != prev_presence:
        timestamp_str = time.strftime('%H:%M:%S')
        if is_present:
            print(f"[{timestamp_str}] [INTERVIEW MONITOR] Candidate Present: YES (Detected via {detection_type})")
        else:
            print(f"[{timestamp_str}] [INTERVIEW MONITOR] Candidate Present: NO  (Candidate Left Camera Frame)")
        prev_presence = is_present

    # FPS Calculation
    curr_time = time.time()
    fps = 1.0 / (curr_time - prev_time) if (curr_time - prev_time) > 0 else 0
    prev_time = curr_time

    # UI Visual Styling
    if is_present:
        status_text = "YES"
        sub_text = "CANDIDATE PRESENT & VERIFIED"
        theme_color = (0, 215, 0)       # Bright Green
        border_color = (0, 255, 0)
        bg_bar_color = (25, 48, 25)
    else:
        status_text = "NO"
        sub_text = "CANDIDATE ABSENT / NOT IN FRAME"
        theme_color = (0, 0, 230)       # Bright Red
        border_color = (0, 0, 255)
        bg_bar_color = (25, 25, 48)

    # Draw Tracking Box when candidate is detected
    if is_present and len(detected_boxes) > 0:
        for (bx, by, bw, bh) in detected_boxes:
            cv2.rectangle(frame, (bx, by), (bx + bw, by + bh), (0, 255, 0), 2)
            tag = f"CANDIDATE ({detection_type.split(' ')[0]})"
            cv2.putText(frame, tag, (bx, by - 8), cv2.FONT_HERSHEY_SIMPLEX, 0.48, (0, 255, 0), 1, cv2.LINE_AA)

    # 1. Top Proctoring Header Bar
    cv2.rectangle(frame, (0, 0), (w, 105), (15, 15, 15), -1)
    cv2.line(frame, (0, 105), (w, 105), border_color, 3)

    # 2. Left Header: Interview Info & Pose Status
    cv2.putText(frame, "INTERVIEW PRESENCE MONITOR", (20, 32), cv2.FONT_HERSHEY_DUPLEX, 0.75, (240, 240, 240), 2, cv2.LINE_AA)
    elapsed_sec = int(curr_time - start_time)
    timer_str = f"Session: {elapsed_sec // 60:02d}:{elapsed_sec % 60:02d} | FPS: {fps:.1f} | Tracking: {detection_type}"
    cv2.putText(frame, timer_str, (20, 60), cv2.FONT_HERSHEY_SIMPLEX, 0.50, (180, 180, 180), 1, cv2.LINE_AA)
    cv2.putText(frame, f"Status: {sub_text}", (20, 88), cv2.FONT_HERSHEY_SIMPLEX, 0.56, theme_color, 2, cv2.LINE_AA)

    # 3. Right Header: Large YES / NO Badge
    badge_w, badge_h = 190, 85
    bx1 = w - badge_w - 20
    by1 = 10
    bx2 = w - 20
    by2 = by1 + badge_h

    cv2.rectangle(frame, (bx1, by1), (bx2, by2), bg_bar_color, -1)
    cv2.rectangle(frame, (bx1, by1), (bx2, by2), border_color, 3)

    cv2.putText(frame, "PRESENT:", (bx1 + 14, by1 + 25), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (200, 200, 200), 1, cv2.LINE_AA)
    yes_no_font_scale = 1.6
    yes_no_x = bx1 + (38 if status_text == "YES" else 48)
    cv2.putText(frame, status_text, (yes_no_x, by1 + 70), cv2.FONT_HERSHEY_DUPLEX, yes_no_font_scale, theme_color, 3, cv2.LINE_AA)

    # 4. Full-frame Alert Border when Absent
    if not is_present:
        cv2.rectangle(frame, (0, 0), (w-1, h-1), (0, 0, 255), 4)

    # 5. Bottom Status Bar
    cv2.rectangle(frame, (0, h - 30), (w, h), (15, 15, 15), -1)
    cv2.putText(frame, "Press 'q' in this window to exit interview session", (20, h - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.45, (160, 160, 160), 1, cv2.LINE_AA)

    cv2.imshow('Interview Presence Monitor', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
print("\n[INFO] Interview session ended.")