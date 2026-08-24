import os
import torch
import torch.nn as nn
import torch.optim as optim
from torchvision import datasets, transforms, models

# 1. Advanced Data Augmentation for Small Datasets
train_transform = transforms.Compose([
    transforms.Resize((240, 240)),
    transforms.RandomResizedCrop(224, scale=(0.8, 1.0)),
    transforms.RandomHorizontalFlip(p=0.5),
    transforms.RandomRotation(degrees=10),
    transforms.ColorJitter(brightness=0.3, contrast=0.3, saturation=0.3, hue=0.05),
    transforms.RandomAffine(degrees=0, translate=(0.08, 0.08)),
    transforms.ToTensor(),
    transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])
])

val_transform = transforms.Compose([
    transforms.Resize((224, 224)),
    transforms.ToTensor(),
    transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])
])

# 2. Load Dataset
data_dir = 'realsense_dataset/rgb'
dataset = datasets.ImageFolder(data_dir, transform=train_transform)
dataloader = torch.utils.data.DataLoader(dataset, batch_size=4, shuffle=True, drop_last=False)

print(f"Loaded {len(dataset)} images belonging to classes: {dataset.classes}")

# 3. Setup Pretrained MobileNetV2 with Fine-Tuning
weights = models.MobileNet_V2_Weights.DEFAULT
model = models.mobilenet_v2(weights=weights)

# Freeze base features, but unfreeze the last high-level feature block for fine-tuning
for param in model.parameters():
    param.requires_grad = False

# Unfreeze the last feature layer (block 18) for better human texture/shape adaptation
for param in model.features[17:].parameters():
    param.requires_grad = True

# Replace the classifier head
model.classifier[1] = nn.Sequential(
    nn.Dropout(p=0.2),
    nn.Linear(model.last_channel, 2)
)

# 4. Optimizer & Loss Function
criterion = nn.CrossEntropyLoss(label_smoothing=0.05)
optimizer = optim.AdamW([
    {'params': model.features[17:].parameters(), 'lr': 1e-4, 'weight_decay': 1e-3},
    {'params': model.classifier.parameters(), 'lr': 1e-3, 'weight_decay': 1e-3}
])
epochs = 30
scheduler = optim.lr_scheduler.CosineAnnealingLR(optimizer, T_max=epochs)

# 5. Train Model
print("\nStarting enhanced training with data augmentation & fine-tuning...")
model.train()

for epoch in range(epochs):
    running_loss = 0.0
    correct = 0
    total = 0
    for inputs, labels in dataloader:
        optimizer.zero_grad()
        outputs = model(inputs)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()
        
        running_loss += loss.item() * inputs.size(0)
        _, preds = torch.max(outputs, 1)
        correct += torch.sum(preds == labels.data).item()
        total += inputs.size(0)
        
    scheduler.step()
    epoch_loss = running_loss / total
    epoch_acc = (correct / total) * 100.0
    if (epoch + 1) % 5 == 0 or epoch == 0:
        print(f"Epoch {epoch+1:02d}/{epochs:02d} - Loss: {epoch_loss:.4f} - Acc: {epoch_acc:.1f}%")

# 6. Save Model
torch.save(model.state_dict(), 'human_detector.pth')
print("\n[SUCCESS] Enhanced model saved as 'human_detector.pth'")