#include <stdio.h>
int leapyear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        return 1;
    else
        return 0;
}
int main()
{
    int year;
    printf("Enter a year: ");
    scanf("%d", &year);

    if (year < 1901)
    {
        printf("Please enter year >= 1901.\n");
        return 1;
    }

    int totalDays = 0;

    for (int i = 1901; i < year; i++)
    {
        if (leapyear(i))
            totalDays += 366;
        else
            totalDays += 365;
    }

    int dayIndex = totalDays % 7;

    char *days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    printf("%s.\n", days[dayIndex]);

    return 0;
}
