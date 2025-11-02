package Package1;

public class A {
    public int pubVar = 10;
    protected int proVar = 20;
    int defVar = 30; // default access
    private int priVar = 40;

    public void display() {
        System.out.println("Inside A:");
        System.out.println("Public: " + pubVar);
        System.out.println("Protected: " + proVar);
        System.out.println("Default: " + defVar);
        System.out.println("Private: " + priVar);
    }
}
