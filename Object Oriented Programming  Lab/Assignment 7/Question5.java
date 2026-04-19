//package main;
import Package1.A;
import Package2.B;
import Package2.C;

public class Question5 {
    public static void main(String[] args) {
        A objA = new A();
        B objB = new B();
        C objC = new C();

        objA.display();     // Access within same class
        objB.showAccess();  // Access in subclass (different package)
        objC.showAccess();  // Access in non-subclass (different package)
    }
}
