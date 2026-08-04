import geometry.*;
import java.util.Scanner;

public class MainGeometry {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Circle c = new Circle();
        Rectangle r = new Rectangle();
        Triangle t = new Triangle();

        System.out.print("Enter radius: ");
        double rad = sc.nextDouble();
        System.out.println("Circle Area: " + c.area(rad));

        System.out.print("Enter length and breadth: ");
        double l = sc.nextDouble(), b = sc.nextDouble();
        System.out.println("Rectangle Area: " + r.area(l, b));

        System.out.print("Enter base and height: ");
        double base = sc.nextDouble(), h = sc.nextDouble();
        System.out.println("Triangle Area: " + t.area(base, h));
    }
}
