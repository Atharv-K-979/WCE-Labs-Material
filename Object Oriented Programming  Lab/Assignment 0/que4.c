#include<stdio.h>
#include<string.h>

struct telemetry {
    int ID;
    char type[20];
    union {
        struct {
            float r1, r2;
        } thermal;

        struct {
            float r1;
            int r2;
        } pressure;

        float velocity[3];
    } data;
};

int main() {
    struct telemetry t1;

    printf("Enter packet ID: ");
    scanf("%d", &t1.ID);

    printf("Enter type of data (thermal / pressure / velocity): ");
    scanf("%s", t1.type);

    if (strcmp(t1.type, "thermal") == 0) {
        printf("Enter 2 thermal readings: ");
        scanf("%f %f", &t1.data.thermal.r1, &t1.data.thermal.r2);
        printf("Stored Thermal Readings: %.2f %.2f\n", t1.data.thermal.r1, t1.data.thermal.r2);
    }
    else if (strcmp(t1.type, "pressure") == 0) {
        printf("Enter 1 float and 1 int pressure readings: ");
        scanf("%f %d", &t1.data.pressure.r1, &t1.data.pressure.r2);
        printf("Stored Pressure Readings: %.2f %d\n", t1.data.pressure.r1, t1.data.pressure.r2);
    }
    else if (strcmp(t1.type, "velocity") == 0) {
        printf("Enter 3 velocity readings: ");
        for (int i = 0; i < 3; i++) {
            scanf("%f", &t1.data.velocity[i]);
        }
        printf("Stored Velocity Readings: ");
        for (int i = 0; i < 3; i++) {
            printf("%.2f ", t1.data.velocity[i]);
        }
        printf("\n");
    }
    else {
        printf("Unknown type entered!\n");
    }

    return 0;
}
