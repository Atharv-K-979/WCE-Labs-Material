#include <stdio.h>
#include <string.h>

struct student
{
    int ID;
    char name[100];
    float marks[5];
    char resultType[10];
};

int main()
{
    int n, i, j;
    printf("Enter number of students: ");
    scanf("%d", &n);

    struct student students[n];

    for (i = 0; i < n; i++)
    {
        printf("Enter ID for student %d: ", i + 1);
        scanf("%d", &students[i].ID);

        printf("Enter name for student %d: ", i + 1);
        scanf(" %[^\n]", students[i].name); //  %[^\n] Lua char avoids newline

        printf("Enter marks of 5 subjects for student %d: ", i + 1);
        for (j = 0; j < 5; j++)
        {
            scanf("%f", &students[i].marks[j]);
        }

        printf("Enter result type (Grade or Pass/Fail) for student %d: ", i + 1);
        scanf("%s", students[i].resultType);
    }

    printf("\nStudent Records:\n");
    for (i = 0; i < n; i++)
    {
        printf("ID: %d\n", students[i].ID);
        printf("Name: %s\n", students[i].name);
        printf("Marks: ");
        for (j = 0; j < 5; j++)
        {
            printf("%.2f ", students[i].marks[j]);
        }
        printf("\nResult Type: %s\n\n", students[i].resultType);
    }

    return 0;
}
