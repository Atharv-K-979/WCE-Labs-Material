#include <stdio.h>
#include <string.h>
#include <stdlib.h> // this fun allows use of malloc.h and free function

char *zones[] = {"south", "east", "north", "west"}; // 0 for south and so on..

typedef struct
{
    int id;
    char timestamp[50];
    char zone[20];
} Sensor;

void addsensor(Sensor *sensors, int i)
{
    printf("Enter id, timestamp and zone index (0=south, 1=east, 2=north, 3=west):\n");
    int z;
    scanf("%d %s %d", &sensors[i].id, sensors[i].timestamp, &z);

    if (z < 0 || z > 3)
    {
        printf("Invalid zone index. Setting zone to 'unknown'.\n");
        strcpy(sensors[i].zone, "unknown");
    }
    else
    {
        strcpy(sensors[i].zone, zones[z]);
    }
}

void displayOne(Sensor *s)
{
    printf("Sensor ID: %d\n", s->id);
    printf("Timestamp: %s\n", s->timestamp);
    printf("Zone: %s\n\n", s->zone);
}

void display(Sensor *sensors, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Sensor %d:\n", i + 1);
        displayOne(&sensors[i]);
    }
}

int main()
{
    int size;
    printf("Enter number of sensors: ");
    scanf("%d", &size);

    Sensor *sensors = (Sensor *)malloc(sizeof(Sensor) * size);
    if (!sensors)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }
    for (int i = 0; i < size; i++)
    {
        addsensor(sensors, i);
    }

    display(sensors, size);
    free(sensors);
    return 0;
}
