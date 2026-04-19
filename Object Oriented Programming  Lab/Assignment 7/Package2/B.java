package Package2;
import Package1.A;

public class B extends A {
    public void showAccess() {
        System.out.println("\nInside subclass B (in different package):");
        System.out.println("Public variable: " + pubVar);
        System.out.println("Protected variable (accessible via inheritance): " + proVar);
        // System.out.println(defVar); // ❌ Not accessible (default)
        // System.out.println(priVar); // ❌ Not accessible (private)
    }
}
