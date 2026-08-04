class Car {
    private boolean isLocked;
    private boolean isStarted;
    public Car() {
        isLocked = true;
        isStarted = false;
    }
    public void unlockCar() {
        if (!isLocked) {
            System.out.println("Car is already unlocked.");
        } else {
            isLocked = false;
            System.out.println("Car is now unlocked.");
        }
    }
    public void lockCar() {
        if (isStarted) {
            System.out.println("Can't lock the car while it's running!");
        } else if (isLocked) {
            System.out.println("Car is already locked.");
        } else {
            isLocked = true;
            System.out.println("Car is now locked.");
        }
    }
    public void startCar() {
        if (isLocked) {
            System.out.println("Cannot start the car. It is locked.");
        } else if (isStarted) {
            System.out.println("Car is already started.");
        } else {
            isStarted = true;
            System.out.println("Car has started!");
        }
    }
    public void stopCar() {
        if (!isStarted) {
            System.out.println("Car is not running.");
        } else {
            isStarted = false;
            System.out.println("Car has stopped.");
        }
    }
}
public class CarSimulation {
    public static void main(String[] args) {
        Car myCar = new Car();
        myCar.startCar();   
        myCar.unlockCar();  
        myCar.startCar();  
        myCar.lockCar();    
        myCar.stopCar();    
        myCar.lockCar();   
    }
}