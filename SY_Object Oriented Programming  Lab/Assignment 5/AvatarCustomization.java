import java.util.ArrayList;
abstract class AvatarFeature {
    protected String featureName;

    public AvatarFeature(String featureName) {
        this.featureName = featureName;
    }
    // Method to be overridden by subclasses
    public abstract void applyFeature();
}
// SkinFeature subclass
class SkinFeature extends AvatarFeature {
    private String skinTone;

    public SkinFeature(String skinTone) {
        super("Skin Feature");
        this.skinTone = skinTone;
    }
    @Override
    public void applyFeature() {
        System.out.println("Applying skin feature: " + skinTone + " tone.");
    }
}
// OutfitFeature subclass
class OutfitFeature extends AvatarFeature {
    private String outfitStyle;
    public OutfitFeature(String outfitStyle) {
        super("Outfit Feature");
        this.outfitStyle = outfitStyle;
    }
    public void applyFeature() {
        System.out.println("Applying outfit feature: " + outfitStyle + " style.");
    }
}
// VoiceFeature subclass
class VoiceFeature extends AvatarFeature {
    private String voiceType;
    public VoiceFeature(String voiceType) {
        super("Voice Feature");
        this.voiceType = voiceType;
    }
    public void applyFeature() {
        System.out.println("Applying voice feature: " + voiceType + " voice.");
    }
}
// Main class
public class AvatarCustomization {
    public static void main(String[] args) {
        // Using runtime polymorphism: store different features in a common list
        ArrayList<AvatarFeature> features = new ArrayList<>();
        features.add(new SkinFeature("Olive"));
        features.add(new OutfitFeature("Knight Armor"));
        features.add(new VoiceFeature("Deep Bass"));
        features.add(new OutfitFeature("Casual Wear"));
        features.add(new SkinFeature("Pale"));
        // Apply all features dynamically
        System.out.println("Applying Avatar Customizations:");
        for (AvatarFeature feature : features) {
            feature.applyFeature();
        }
    }
}