package Package2;
import Package1.A;

public class C {
    public void showAccess() {
        A obj = new A();
        System.out.println("\nInside class C (non-subclass, different package):");
        System.out.println("Public variable: " + obj.pubVar);
        // System.out.println(obj.proVar); // ❌ Not accessible
        // System.out.println(obj.defVar); // ❌ Not accessible
        // System.out.println(obj.priVar); // ❌ Not accessible
    }
}
