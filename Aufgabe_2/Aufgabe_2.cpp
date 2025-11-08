// Aufgabe_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

void Calculate(uint8_t* array, uint8_t size);
int Analyse(uint8_t* array, uint8_t size);
int main()
{
    printf("Hello World!\n");
    uint8_t size = 1000 / 8;
    uint8_t* array= (uint8_t*)malloc(size);
    if (!array) return -1;
    memset(array,0xFF,size);
    Calculate(array, size);
    printf("%d,\n",Analyse(array, size));
}

void Calculate(uint8_t* array, uint8_t size)
{
    for (uint8_t i = 0; i <= size; i++)
    {
        for (int l = 0; l < 8; l++)
        {
            int number = i * 8 + l + 2;
            int p = number;
            int numberToExclude = number * p;
            while (numberToExclude < size * 8)
            {
                uint8_t exclude_index = (numberToExclude - 2) / 8;
                uint8_t array_value = array[exclude_index];
                uint8_t mask = ~(1 << (7 - (numberToExclude - 2) % 8));
                array_value &= mask;
                array[exclude_index] = array_value;
                p++;
                numberToExclude = number * p;
            }
        }
    }
}

int Analyse(uint8_t* array, uint8_t size)
{
    int result = 0;
    for (int i = 0; i < size; i++)
    {
        uint8_t array_value = array[i];
        for (int l = 0; l < 8; l++)
        {
            bool value = (array_value >> (7 - l)) & 1;
            if (value)
            {
                result++;
                printf("%d,\n", i * 8 + l + 2);
            }
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
