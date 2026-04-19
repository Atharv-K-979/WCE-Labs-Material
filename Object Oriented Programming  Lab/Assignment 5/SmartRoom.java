// SmartRoom.java
public class SmartRoom {
    // Attributes
    private int roomNumber;
    private boolean isOccupied;
    private double temperature;
    private String lightingMode;
    // Default constructor
    public SmartRoom() {
        this.roomNumber = 0;
        this.isOccupied = false;
        this.temperature = 22.0; // Standard temperature
        this.lightingMode = "Off"; // Lights off by default
    }
    // Parameterized constructor
    public SmartRoom(int roomNumber, boolean isOccupied, double temperature, String lightingMode) {
        this.roomNumber = roomNumber;
        this.isOccupied = isOccupied;
        this.temperature = temperature;
        this.lightingMode = lightingMode;
    }
    // Method to display room configuration
    public void displayRoomConfig() {
        System.out.println("Room Number: " + roomNumber);
        System.out.println("Occupancy Status: " + (isOccupied ? "Occupied" : "Empty"));
        System.out.println("Temperature Setting: " + temperature + "°C");
        System.out.println("Lighting Mode: " + lightingMode);
    }
    public static void main(String[] args) {
        // Using default constructor
        SmartRoom defaultRoom = new SmartRoom();
        System.out.println("Default Room Configuration:");
        defaultRoom.displayRoomConfig();
        // Using parameterized constructor
        SmartRoom conferenceRoom = new SmartRoom(101, true, 24.5, "Bright");
        SmartRoom loungeRoom = new SmartRoom(102, false, 21.0, "Dim");
        System.out.println("Custom Room Configurations:");
        conferenceRoom.displayRoomConfig();
        loungeRoom.displayRoomConfig();
    }
}