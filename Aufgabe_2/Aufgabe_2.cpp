// Aufgabe_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

void Calculate(bool* array);
int Analyse(bool* array);
int main()
{
    printf("Hello World!\n");

    bool* array= (bool*)malloc(998);
    if (!array) return -1;
    memset(array,1,sizeof(array));
    Calculate(array);
    printf("%d,\n",Analyse(array));
}

void Calculate(bool* array)
{
    for (int i = 0; i <= 998; i++)
    {
        if (!array[i]) continue;
        int number = i + 2;
        int p = number;
        int numberToExclude = number * p;
        while (numberToExclude < 1000)
        {
            array[numberToExclude - 2] = 0;
            p++;
            numberToExclude = number * p;
        }
    }
}

int Analyse(bool * array)
{
    int result = 0;
    for (int i = 0; i < 998; i++)
    {
        if (array[i])
        {
            result++;
            printf("%d,\n",i+2);
        }
    }
    return result;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
