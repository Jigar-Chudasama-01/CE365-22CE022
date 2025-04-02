#include<stdio.h>
#include<conio.h>

int main()
{
    char input[50];
    int i;

    printf("Enter the String:");
    scanf("%s",input);

    while (input[i] == 'a') {
        i++;
    }

    if (input[i] == 'b' && input[i + 1] == 'b' && input[i + 2] == '\0') {
        printf("Valid String \n");
    } else {
        printf("Invalid String \n");
    }

    return 0;
}
