#include<stdio.h>
#include<conio.h>


int main()
{
    int numStates, numSymbols, numAcceptingStates,initialState, currentState, acceptingStates;
    char inputString[100];
    char symbols;


    printf("Number of input symbols: ");
    scanf("%d",&numSymbols);
    printf("Input symbols: ");
    for (int i = 0; i < numSymbols; i++) {
        scanf("%c",&symbols);
    }

    printf("Enter number of states: ");
    scanf("%d", &numStates);

    printf("Initial state: ");
    scanf("%d", &initialState);

    printf("Number of accepting states: ");
    scanf("%d", &numAcceptingStates);
    printf("Accepting states: ");
    for (int i = 0; i < numAcceptingStates; i++) {
        scanf("%d", &acceptingStates);
    }

}
