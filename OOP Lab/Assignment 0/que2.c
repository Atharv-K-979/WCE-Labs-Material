#include <stdio.h>
#include <string.h>
#include <stdlib.h> // for malloc and free functions

// Zone names mapped by index: 0 = south, 1 = east, 2 = north, 3 = west
char *zones[] = {"south", "east", "north", "west"};

typedef struct
{
    int id;              // Sensor ID
    char timestamp[50];  // Time when reading was taken
    char zone[20];       // Zone name of the sensor
} Sensor;

// Function to add details of one sensor
void addsensor(Sensor *sensors, int i)
{
    printf("Enter id, timestamp and zone index (0=south, 1=east, 2=north, 3=west):\n");
    int z; // temporary variable for zone index
    scanf("%d %s %d", &sensors[i].id, sensors[i].timestamp, &z);

    // Check if the entered zone index is valid
    if (z < 0 || z > 3)
    {
        printf("Invalid zone index. Setting zone to 'unknown'.\n");
        strcpy(sensors[i].zone, "unknown");
    }
    else
    {
        // Copy the corresponding zone name from zones array
        strcpy(sensors[i].zone, zones[z]);
    }
}

// Function to display one sensor's details
void displayOne(Sensor *s)
{
    printf("Sensor ID: %d\n", s->id);
    printf("Timestamp: %s\n", s->timestamp);
    printf("Zone: %s\n\n", s->zone);
}

// Function to display all sensors
void display(Sensor *sensors, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Sensor %d:\n", i + 1);
        displayOne(&sensors[i]); // print details of each sensor
    }
}

int main()
{
    int size; // number of sensors
    printf("Enter number of sensors: ");
    scanf("%d", &size);

    // Dynamically allocate memory for the sensors array
    Sensor *sensors = (Sensor *)malloc(sizeof(Sensor) * size);
    if (!sensors) // check if allocation failed
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Input all sensor details
    for (int i = 0; i < size; i++)
    {
        addsensor(sensors, i);
    }

    // Display all entered sensor information
    display(sensors, size);

    // Free allocated memory to avoid memory leaks
    free(sensors);
    return 0;
}
