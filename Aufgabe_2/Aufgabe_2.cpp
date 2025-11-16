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
        uint8_t array_value = array[i];
        int l = 0;
        if (i == 0) l = 2;
        for (; l < 8; l++)
        {
            int number = i * 8 + l;
            
            int p = number;
            int numberToExclude = number * p;
            while (numberToExclude < size * 8)
            {
                uint8_t exclude_index = (numberToExclude) / 8;
                uint8_t array_value = array[exclude_index];
                uint8_t mask = ~(1 << (7 - (numberToExclude) % 8));
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
        int l = 0;
        if (i == 0) l = 2;
        uint8_t array_value = array[i];
        for (; l < 8; l++)
        {
            bool value = (array_value >> (7 - l)) & 1;
            if (value)
            {
                result++;
                printf("%d,\n", i * 8 + l);
            }
        }
    }
    return result;
}

// Speicher zugriff - 8 numbers for index
//       |    2-9   | 10-18 |
// index | 0        | 1 | 2 | 3 | 4 | 5 | 6 | 7 |... | 1000 |
// value | 11010100 | 1 | 0 | 1 | 0 | 1 ... | 0    |