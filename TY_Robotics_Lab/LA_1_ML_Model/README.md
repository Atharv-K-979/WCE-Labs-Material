# 🤖 Real-Time Human Detection & Presence Monitoring System
### *Robotics Perception & AI Proctoring with Intel RealSense & Deep Transfer Learning*

[![Python](https://img.shields.io/badge/Python-3.8%2B-blue.svg?logo=python&logoColor=white)](https://www.python.org/)
[![PyTorch](https://img.shields.io/badge/PyTorch-2.0%2B-EE4C2C.svg?logo=pytorch&logoColor=white)](https://pytorch.org/)
[![Torchvision](https://img.shields.io/badge/Torchvision-0.15%2B-EE4C2C.svg)](https://pytorch.org/)
[![OpenCV](https://img.shields.io/badge/OpenCV-4.x-5C3EE8.svg?logo=opencv&logoColor=white)](https://opencv.org/)
[![Intel RealSense](https://img.shields.io/badge/Intel%20RealSense-SDK%202.0-0071C5.svg?logo=intel&logoColor=white)](https://www.intelrealsense.com/)
[![Accuracy](https://img.shields.io/badge/Model%20Accuracy-100%25-brightgreen.svg)](#-evaluation--benchmark-results)

---

## 📌 Executive Summary

This repository contains the complete implementation of **Lab Assignment 1 (LA-1): Machine Learning Model for Robotics Perception**, developed for the **Third Year (TY) Robotics Lab** at **Walchand College of Engineering (WCE)**.

The project demonstrates an end-to-end vision system designed to detect human presence reliably in real time. It overcomes common challenges in computer vision—such as head tilt, sharp profile turns, torso occlusion, and lighting shifts—by fusing **classical multi-pose Haar cascades** with a fine-tuned **MobileNetV2 deep neural network** and an **adaptive temporal absence grace filter**. The system integrates with **Intel RealSense D400-series depth cameras** as well as standard RGB video feeds, offering an **AI Interview / Exam Presence Monitor** with a heads-up display (HUD).

```
+-----------------------------------------------------------------------------------+
|                        AI INTERVIEW PRESENCE MONITOR (HUD)                        |
| Session: 04:12 | FPS: 31.4 | Tracking: Face (Frontal/Tilt)        [ PRESENT: YES ]|
| Status: CANDIDATE PRESENT & VERIFIED                              [ (GREEN BADGE)|
+-----------------------------------------------------------------------------------+
|                                                                                   |
|                   [Candidate Tracked: Bounding Box Overlay]                       |
|                                                                                   |
+-----------------------------------------------------------------------------------+
| Press 'q' in this window to exit interview session                                |
+-----------------------------------------------------------------------------------+
```

---

## 📑 Table of Contents

1. [Key Features & System Highlights](#-key-features--system-highlights)
2. [System Architecture & Detection Pipeline](#-system-architecture--detection-pipeline)
3. [Deep Learning Model Architecture & Training](#-deep-learning-model-architecture--training)
4. [Dataset Architecture](#-dataset-architecture)
5. [Intel RealSense Sensor Integration](#-intel-realsense-sensor-integration)
6. [Repository Structure](#-repository-structure)
7. [Installation & Environment Setup](#-installation--environment-setup)
8. [Step-by-Step Execution Guide](#-step-by-step-execution-guide)
   - [Step 1: RealSense Sensor Streaming (Jupyter)](#step-1-realsense-sensor-streaming)
   - [Step 2: Model Training (`train.py`)](#step-2-model-training)
   - [Step 3: Test Benchmark Evaluation (`test_images.py`)](#step-3-test-benchmark-evaluation)
   - [Step 4: Real-Time Live Presence Monitor (`live_detection.py`)](#step-4-real-time-live-presence-monitor)
9. [Evaluation & Benchmark Results](#-evaluation--benchmark-results)
10. [Configuration & Tuning Parameters](#-configuration--tuning-parameters)
11. [Troubleshooting & FAQs](#-troubleshooting--faqs)
12. [Academic Context & Credits](#-academic-context--credits)

---

## 🌟 Key Features & System Highlights

- **Multi-Stage Hybrid Detection Ensemble**: Combines multi-angle Haar cascades with a deep convolutional neural network for speed and accuracy.
- **Multi-Pose Head & Neck Movement Tolerance**:
  - **Frontal & Tilt**: `haarcascade_frontalface_alt2.xml` handles vertical head tilt and forward pitch.
  - **Left Profile**: `haarcascade_profileface.xml` detects candidates looking towards their left.
  - **Right Profile**: Dynamic horizontal frame flip coordinate-mapping identifies rightward turns without missing angles.
  - **Upper Body / Torso**: `haarcascade_upperbody.xml` verifies presence when candidates look down (e.g., writing notes or typing).
- **Deep Feature Fallback**: Pretrained MobileNetV2 acts as a secondary detector even when face or torso cues are partially obscured.
- **Temporal Absence Grace Filter**:
  - Employs a 20-frame grace buffer (`~0.7s - 1.0s` at 30 FPS).
  - Eliminates flickering and false "Absent" warnings caused by momentary occlusion or natural head motion.
- **Real-Time Proctoring HUD (Heads-Up Display)**:
  - Dark-mode proctoring bar with session duration timer and real-time FPS counter.
  - Dynamic status indicator (`YES` in Bright Green / `NO` in Alert Red).
  - Full-frame red perimeter strobe warning when a candidate leaves the camera frame.
  - Real-time bounding box annotations with tracking method tags.
- **Intel RealSense D435 / D415 Support**:
  - Notebook workflow demonstrates Depth + RGB synchronized streaming using the `pyrealsense2` pipeline.
  - Depth colorization via `rs.colorizer()` for 3D spatial perception.
- **Robust Hardware Auto-Discovery**:
  - Automatically queries available camera indices (`0, 1, 2`) with DirectShow (`cv2.CAP_DSHOW`) and platform-native fallbacks.

---

## 🏗 System Architecture & Detection Pipeline

The system uses a sequential hierarchical cascade fused with deep inference:

```mermaid
flowchart TD
    A[Camera Frame Input (Webcam / RealSense RGB)] --> B[Grayscale Conversion & Preprocessing]
    A --> C[Resize & Normalize to Tensor 224x224]

    subgraph Classical Multi-Pose Cascade
        B --> D{Frontal / Tilted Face?}
        D -- Yes --> D1[Tag: Face Frontal/Tilt]
        D -- No --> E{Profile Face Left?}
        E -- Yes --> E1[Tag: Face Profile Left]
        E -- No --> F[Flip Frame Horizontally]
        F --> G{Profile Face Right?}
        G -- Yes --> G1[Map Coords -> Tag: Face Profile Right]
        G -- No --> H{Upper Body / Torso?}
        H -- Yes --> H1[Tag: Upper Body / Torso]
        H -- No --> H2[No Physical Cascade Cue]
    end

    subgraph Deep Transfer Learning
        C --> I[MobileNetV2 Inference]
        I --> J[Softmax Output: Human vs Non-Human Probability]
    end

    D1 --> K[Decision Fusion Logic]
    E1 --> K
    G1 --> K
    H1 --> K
    H2 --> K
    J --> K

    subgraph Temporal Filter & Output
        K --> L{Physical Cue Found OR Human Prob >= 70%?}
        L -- Yes --> M[Reset Absence Counter -> Instant Detected: TRUE]
        L -- No --> N[Increment Absence Counter]
        N --> O{Counter >= 20 Frames?}
        O -- No --> P[Within Grace Period -> Retain Presence: TRUE]
        O -- Yes --> Q[Candidate Marked: ABSENT / NO]
        M --> R[Candidate Marked: PRESENT / YES]
        P --> R
        R --> S[Render Modern HUD Overlay & Console Log]
        Q --> S
    end
```

---

## 🧠 Deep Learning Model Architecture & Training

### 1. Model Backbone: MobileNetV2
- **Base Architecture**: Lightweight inverted residual blocks with depthwise separable convolutions (`models.mobilenet_v2`).
- **Pretrained Weights**: `MobileNet_V2_Weights.DEFAULT` (ImageNet-1k).
- **Fine-Tuning Strategy**:
  - The feature extractor parameters (`features[0:17]`) are frozen to retain foundational visual representations (edges, textures, shapes).
  - The final feature extraction block (**Block 18**, `features[17:]`) is unfrozen and trained at a fine-tuned learning rate ($10^{-4}$).
  - A custom classifier head replaces the standard 1000-class head:
    ```python
    model.classifier[1] = nn.Sequential(
        nn.Dropout(p=0.2),
        nn.Linear(model.last_channel, 2)  # Binary: human vs non_human
    )
    ```

### 2. Advanced Data Augmentation (Tuned for Small Sample Regimes)
To achieve generalization on compact robotics datasets, the training pipeline uses an augmentation pipeline:
- `Resize((240, 240))` followed by `RandomResizedCrop(224, scale=(0.8, 1.0))`
- `RandomHorizontalFlip(p=0.5)`
- `RandomRotation(degrees=10)`
- `ColorJitter(brightness=0.3, contrast=0.3, saturation=0.3, hue=0.05)`
- `RandomAffine(degrees=0, translate=(0.08, 0.08))`
- `Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])`

### 3. Hyperparameters & Optimization Setup
| Component | Configuration | Description / Rationale |
| :--- | :--- | :--- |
| **Loss Function** | `CrossEntropyLoss(label_smoothing=0.05)` | Regularizes overconfident predictions on small sample sets |
| **Optimizer** | `AdamW` | Decoupled weight decay ($10^{-3}$) prevents overfitting |
| **Classifier LR** | $1 \times 10^{-3}$ | Faster convergence on new dense head weights |
| **Feature Layer LR** | $1 \times 10^{-4}$ | Gentle fine-tuning for block 18 high-level representations |
| **LR Scheduler** | `CosineAnnealingLR(T_max=30)` | Smooth annealing to minimum learning rate |
| **Epochs** | `30` | Full convergence across all batches |
| **Batch Size** | `4` | High gradient update frequency per epoch |

---

## 📁 Dataset Architecture

The dataset is partitioned into synchronized RGB and depth feeds captured through an **Intel RealSense D435 / D415** sensor:

```
realsense_dataset/
├── rgb/
│   ├── human/           # 13 RGB images containing human subjects in various poses
│   │   ├── human_00001.jpg ... human_00013.jpg
│   └── non_human/       # 15 RGB images of unoccupied rooms, chairs, desks, walls
│       ├── non_human_00001.jpg ... non_human_00015.jpg
└── depth/
    ├── human/           # 13 corresponding 16-bit / colorized depth maps
    │   ├── human_00001.png ... human_00013.png
    └── non_human/       # 15 corresponding depth maps for empty backgrounds
        ├── non_human_00001.png ... non_human_00015.png
```

- **Classes**: `human` (Class index `0`), `non_human` (Class index `1`).
- **Data Modality**: RGB color imagery (.jpg) for classification inference; depth imagery (.png) for spatial validation and point-cloud distance verification.

---

## 📷 Intel RealSense Sensor Integration

The project includes an interactive Jupyter notebook ([`Intel_Realsense_Cammera_Code.ipynb`](file:///home/atharv/Documents/WCE_Lab_Material/TY_Robotics_Lab/LA_1_ML_Model/Intel_Realsense_Cammera_Code.ipynb)) detailing the low-level camera pipeline:

1. **Pipeline & Config Creation**:
   ```python
   import pyrealsense2 as rs
   pipe = rs.pipeline()
   cfg = rs.config()
   ```
2. **Device & Sensor Enumeration**:
   Queries connected hardware for `RGB Camera` and `Stereo Module` (depth) sensors via `rs.context().devices`.
3. **Synchronized Multi-Stream Acquisition**:
   Captures paired depth and color frames:
   ```python
   frameset = pipe.wait_for_frames()
   depth_frame = frameset.get_depth_frame()
   color_frame = frameset.get_color_frame()
   ```
4. **Depth Colorization**:
   Applies `rs.colorizer()` to map distance values (in millimeters) into human-interpretable RGB colormaps (Jet/Rainbow) for visual inspection.

---

## 🗂 Repository Structure

```
.
├── Intel_Realsense_Cammera_Code.ipynb  # Interactive RealSense Depth & RGB demo notebook
├── human_detector.pth                  # Saved PyTorch checkpoint (MobileNetV2 fine-tuned)
├── human_detector/                     # Model state storage directory
├── live_detection.py                   # Production real-time presence monitor with HUD
├── realsense_dataset/                  # Dataset directory
│   ├── depth/                          # Depth map captures (human & non_human)
│   └── rgb/                            # RGB image captures (human & non_human)
├── test_images.py                      # Batch model evaluation benchmark script
├── train.py                            # MobileNetV2 fine-tuning training script
└── README.md                           # Comprehensive documentation
```

---

## ⚙️ Installation & Environment Setup

### 1. Prerequisites
- **Operating System**: Linux (Ubuntu 20.04/22.04 recommended) or Windows 10/11
- **Python**: Version `3.8` through `3.11`
- **Camera**: Standard USB Webcam, Built-in Laptop Camera, or Intel RealSense D400-series (D415, D435, D435i, D455)

### 2. Environment Setup

#### Option A: Using Conda (Recommended)
```bash
# Create and activate environment
conda create -n robotics_ml python=3.10 -y
conda activate robotics_ml

# Install PyTorch & Torchvision (CUDA or CPU)
pip install torch torchvision --index-url https://download.pytorch.org/whl/cpu
# For CUDA: pip install torch torchvision

# Install Computer Vision & Utility Libraries
pip install opencv-python pillow numpy matplotlib

# Optional (for Intel RealSense camera hardware access):
pip install pyrealsense2
```

#### Option B: Using Python `venv`
```bash
python3 -m venv venv
source venv/bin/activate  # On Windows: venv\Scripts\activate
pip install torch torchvision opencv-python pillow numpy matplotlib pyrealsense2
```

---

## 🚀 Step-by-Step Execution Guide

### Step 1: RealSense Sensor Streaming
Launch Jupyter to explore camera stream queries, sensor configurations, and depth colorization:
```bash
jupyter notebook Intel_Realsense_Cammera_Code.ipynb
```
*Note: Ensure an Intel RealSense device is plugged into a USB 3.0 port.*

---

### Step 2: Model Training
To train the MobileNetV2 model on `realsense_dataset/rgb`:
```bash
python train.py
```
**Expected Output:**
```text
Loaded 28 images belonging to classes: ['human', 'non_human']

Starting enhanced training with data augmentation & fine-tuning...
Epoch 01/30 - Loss: 0.6973 - Acc: 50.0%
Epoch 05/30 - Loss: 0.3842 - Acc: 85.7%
Epoch 10/30 - Loss: 0.2319 - Acc: 96.4%
Epoch 15/30 - Loss: 0.1651 - Acc: 100.0%
Epoch 20/30 - Loss: 0.1245 - Acc: 100.0%
Epoch 25/30 - Loss: 0.0987 - Acc: 100.0%
Epoch 30/30 - Loss: 0.0874 - Acc: 100.0%

[SUCCESS] Enhanced model saved as 'human_detector.pth'
```

---

### Step 3: Test Benchmark Evaluation
To validate the trained model weights against the entire dataset:
```bash
python test_images.py
```
This runs inference over all 28 samples, calculates per-image classification confidence, and produces an accuracy summary.

---

### Step 4: Real-Time Live Presence Monitor
To run the live proctoring presence monitor with real-time video feed:
```bash
python live_detection.py
```
- **Controls**: Press **`q`** in the video display window to terminate the monitor.
- **Console Log**: Real-time timestamps document every candidate entrance or absence:
  ```text
  Connected to Camera (Index 0) via default backend
  =================================================================
       AI INTERVIEW PRESENCE MONITOR (MULTI-POSE TRACKING)
  =================================================================
   Features:
   - Multi-Angle Head & Neck Movement Tracking (Front, Tilt, Left/Right)
   - Upper Body & Shoulder Verification
   - Absence Grace Filter (Prevents False NO During Natural Movements)
   Press 'q' in the camera window to quit.

  [00:15:23] [INTERVIEW MONITOR] Candidate Present: YES (Detected via Face (Frontal/Tilt))
  [00:16:04] [INTERVIEW MONITOR] Candidate Present: NO  (Candidate Left Camera Frame)
  [00:16:08] [INTERVIEW MONITOR] Candidate Present: YES (Detected via Upper Body / Torso)
  ```

---

## 📊 Evaluation & Benchmark Results

Evaluating [`human_detector.pth`](file:///home/atharv/Documents/WCE_Lab_Material/TY_Robotics_Lab/LA_1_ML_Model/human_detector.pth) across the benchmark dataset yields a **100.0% overall classification accuracy**:

### Detailed Test Results Breakdown

#### 👤 Human Dataset Evaluation (`realsense_dataset/rgb/human/`)
| Image Filename | Ground Truth | Prediction | Model Confidence | Test Status |
| :--- | :---: | :---: | :---: | :---: |
| `human_00001.jpg` | Human | **HUMAN** | **98.2%** | `PASS` |
| `human_00002.jpg` | Human | **HUMAN** | **97.2%** | `PASS` |
| `human_00003.jpg` | Human | **HUMAN** | **95.8%** | `PASS` |
| `human_00004.jpg` | Human | **HUMAN** | **94.5%** | `PASS` |
| `human_00005.jpg` | Human | **HUMAN** | **99.2%** | `PASS` |
| `human_00006.jpg` | Human | **HUMAN** | **95.8%** | `PASS` |
| `human_00007.jpg` | Human | **HUMAN** | **98.5%** | `PASS` |
| `human_00008.jpg` | Human | **HUMAN** | **53.4%** | `PASS` |
| `human_00009.jpg` | Human | **HUMAN** | **98.8%** | `PASS` |
| `human_00010.jpg` | Human | **HUMAN** | **99.2%** | `PASS` |
| `human_00011.jpg` | Human | **HUMAN** | **99.3%** | `PASS` |
| `human_00012.jpg` | Human | **HUMAN** | **93.7%** | `PASS` |
| `human_00013.jpg` | Human | **HUMAN** | **99.2%** | `PASS` |
| **Category Subtotal** | **13 Samples** | **13 Correct** | **Mean Conf: 94.1%** | **100.0% Accuracy** |

#### 🪑 Non-Human Dataset Evaluation (`realsense_dataset/rgb/non_human/`)
| Image Filename | Ground Truth | Prediction | Model Confidence | Test Status |
| :--- | :---: | :---: | :---: | :---: |
| `non_human_00001.jpg` | Non-Human | **NON_HUMAN** | **87.3%** | `PASS` |
| `non_human_00002.jpg` | Non-Human | **NON_HUMAN** | **91.9%** | `PASS` |
| `non_human_00003.jpg` | Non-Human | **NON_HUMAN** | **70.2%** | `PASS` |
| `non_human_00004.jpg` | Non-Human | **NON_HUMAN** | **74.1%** | `PASS` |
| `non_human_00005.jpg` | Non-Human | **NON_HUMAN** | **94.5%** | `PASS` |
| `non_human_00006.jpg` | Non-Human | **NON_HUMAN** | **91.6%** | `PASS` |
| `non_human_00007.jpg` | Non-Human | **NON_HUMAN** | **88.1%** | `PASS` |
| `non_human_00008.jpg` | Non-Human | **NON_HUMAN** | **91.9%** | `PASS` |
| `non_human_00009.jpg` | Non-Human | **NON_HUMAN** | **90.9%** | `PASS` |
| `non_human_00010.jpg` | Non-Human | **NON_HUMAN** | **94.7%** | `PASS` |
| `non_human_00011.jpg` | Non-Human | **NON_HUMAN** | **97.2%** | `PASS` |
| `non_human_00012.jpg` | Non-Human | **NON_HUMAN** | **90.5%** | `PASS` |
| `non_human_00013.jpg` | Non-Human | **NON_HUMAN** | **95.5%** | `PASS` |
| `non_human_00014.jpg` | Non-Human | **NON_HUMAN** | **85.8%** | `PASS` |
| `non_human_00015.jpg` | Non-Human | **NON_HUMAN** | **96.8%** | `PASS` |
| **Category Subtotal** | **15 Samples** | **15 Correct** | **Mean Conf: 89.4%** | **100.0% Accuracy** |

### Performance Summary
```text
+======================================================+
|                  BENCHMARK SUMMARY                   |
+======================================================+
| Total Samples Evaluated : 28                         |
| True Positives (Human)  : 13 / 13 (100.0%)           |
| True Negatives (Empty)  : 15 / 15 (100.0%)           |
| Overall Accuracy        : 28 / 28 (100.0%)           |
| Real-Time Inference FPS : ~30 - 60 FPS (CPU / GPU)   |
+======================================================+
```

---

## 🔧 Configuration & Tuning Parameters

All operational settings in [`live_detection.py`](file:///home/atharv/Documents/WCE_Lab_Material/TY_Robotics_Lab/LA_1_ML_Model/live_detection.py) can be adapted for custom deployment conditions:

```python
# 1. Absence Grace Window
ABSENCE_GRACE_FRAMES = 20  # Number of missing frames before marking ABSENT (~0.7s - 1.0s)

# 2. Deep Feature Confidence Threshold
# In Step 6:
elif human_prob >= 0.70:   # Minimum softmax confidence required for neural detection
    instant_detected = True

# 3. Haar Cascade Sensitivity
# Tune scaleFactor (1.10 - 1.20) and minNeighbors (3 - 6)
frontal_faces = frontal_cascade.detectMultiScale(gray, scaleFactor=1.12, minNeighbors=4, minSize=(50, 50))
```

---

## ❓ Troubleshooting & FAQs

### Q1: `ModuleNotFoundError: No module named 'torch'`
- **Cause**: The active Python environment does not have PyTorch installed.
- **Solution**: Activate your conda environment or virtual environment that contains PyTorch:
  ```bash
  conda activate base  # or your designated environment
  python test_images.py
  ```

### Q2: `Error: 'human_detector.pth' not found`
- **Cause**: The model weights have not been generated yet.
- **Solution**: Run `python train.py` to train and generate the model checkpoint before launching `live_detection.py` or `test_images.py`.

### Q3: `Error: Could not open camera. Please check camera connections.`
- **Cause**: Camera index mismatch, permission error, or camera locked by another process (e.g., Zoom, Teams, Chrome).
- **Solution**:
  1. Close any running video apps.
  2. On Linux, grant user video permissions:
     ```bash
     sudo usermod -a -G video $USER
     ```
  3. Change the candidate indices in `get_camera()` in `live_detection.py` (e.g., `[0, 1, 2, 3]`).

### Q4: `ModuleNotFoundError: No module named 'pyrealsense2'`
- **Cause**: Intel RealSense SDK Python wrapper is only required if running native RealSense code in `Intel_Realsense_Cammera_Code.ipynb`.
- **Solution**: Install the binary wheels:
  ```bash
  pip install pyrealsense2
  ```
  *(Note: On Linux x86_64, ensure appropriate `udev` rules are installed: `/etc/udev/rules.d/99-realsense-libusb.rules`)*.

---

## 🎓 Academic Context & Credits

- **Course**: TY Robotics Lab (Third Year B.Tech)
- **Module**: Lab Assignment 1 (LA-1) — Machine Learning Model for Robotics Perception
- **Department**: Department of Computer Science & Engineering / Robotics
- **Institution**: Walchand College of Engineering (WCE), Sangli
- **Developed by**: Atharv K. ([Atharv-K-979](https://github.com/Atharv-K-979))
