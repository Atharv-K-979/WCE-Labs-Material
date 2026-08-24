import os
import glob
import torch
import torch.nn as nn
from torchvision import transforms, models
from PIL import Image

def test_all():
    device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
    print(f"Testing with device: {device}")

    # Load model
    model = models.mobilenet_v2(weights=None)
    model.classifier[1] = nn.Sequential(
        nn.Dropout(p=0.2),
        nn.Linear(model.last_channel, 2)
    )
    model.load_state_dict(torch.load('human_detector.pth', map_location=device, weights_only=True))
    model.to(device)
    model.eval()

    transform = transforms.Compose([
        transforms.Resize((224, 224)),
        transforms.ToTensor(),
        transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])
    ])

    classes = ['human', 'non_human']

    # Test Human samples
    human_imgs = sorted(glob.glob('realsense_dataset/rgb/human/*.jpg'))
    non_human_imgs = sorted(glob.glob('realsense_dataset/rgb/non_human/*.jpg'))

    print("\n" + "="*50)
    print("           EVALUATING HUMAN DATASET")
    print("="*50)
    correct_human = 0
    for path in human_imgs:
        img = Image.open(path).convert('RGB')
        tensor = transform(img).unsqueeze(0).to(device)
        with torch.no_grad():
            outputs = model(tensor)
            prob = torch.softmax(outputs, dim=1)[0]
            conf, pred = torch.max(prob, dim=0)
            predicted_class = classes[pred.item()]
            is_correct = (predicted_class == 'human')
            if is_correct: correct_human += 1
            status = "PASS" if is_correct else "FAIL"
            print(f"[{status:4}] {os.path.basename(path):<20} -> {predicted_class.upper()} ({conf.item()*100:.1f}%)")

    print("\n" + "="*50)
    print("        EVALUATING NON-HUMAN DATASET")
    print("="*50)
    correct_non_human = 0
    for path in non_human_imgs:
        img = Image.open(path).convert('RGB')
        tensor = transform(img).unsqueeze(0).to(device)
        with torch.no_grad():
            outputs = model(tensor)
            prob = torch.softmax(outputs, dim=1)[0]
            conf, pred = torch.max(prob, dim=0)
            predicted_class = classes[pred.item()]
            is_correct = (predicted_class == 'non_human')
            if is_correct: correct_non_human += 1
            status = "PASS" if is_correct else "FAIL"
            print(f"[{status:4}] {os.path.basename(path):<20} -> {predicted_class.upper()} ({conf.item()*100:.1f}%)")

    total = len(human_imgs) + len(non_human_imgs)
    acc = ((correct_human + correct_non_human) / total) * 100
    print("\n" + "="*50)
    print(f"  Overall Accuracy: {correct_human + correct_non_human}/{total} ({acc:.1f}%)")
    print("="*50 + "\n")

if __name__ == '__main__':
    test_all()
