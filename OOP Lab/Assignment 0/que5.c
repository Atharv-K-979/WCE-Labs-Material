#include <stdio.h>
#include <string.h>

struct car
{
    char logs[100];
    union
    {
        struct
        {
            int rpm;
            float oiltemp;
        } engine;

        struct
        {
            float pressure;
            float wearval;
        } brake;

        struct
        {
            float voltage;
            float chargelvl;
        } battery;

    } data;
};

int main()
{
    struct car c1;
    printf("Enter car log (engine, brake, battery): ");
    scanf("%s", c1.logs);

    if (strcmp(c1.logs, "engine") == 0)
    {
        printf("Enter rpm and oil temperature: ");
        scanf("%d %f", &c1.data.engine.rpm, &c1.data.engine.oiltemp);
        printf("RPM and oil temperature (in Fahrenheit) of engine is: %d %.2f\n", c1.data.engine.rpm, c1.data.engine.oiltemp);
    }
    else if (strcmp(c1.logs, "brake") == 0)
    {
        printf("Enter pressure and wear level: ");
        scanf("%f %f", &c1.data.brake.pressure, &c1.data.brake.wearval);
        printf("Pressure and wear level of brakes is: %.2f %.2f\n", c1.data.brake.pressure, c1.data.brake.wearval);
    }
    else if (strcmp(c1.logs, "battery") == 0)
    {
        printf("Enter voltage and charge level: ");
        scanf("%f %f", &c1.data.battery.voltage, &c1.data.battery.chargelvl);
        printf("Voltage and charge level of battery is: %.2f %.2f\n", c1.data.battery.voltage, c1.data.battery.chargelvl);
    }
    else
    {
        printf("Unknown log type entered.\n");
    }
    return 0;
}
