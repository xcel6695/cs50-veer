/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
 
bool search(int value, int values[], int n)
{
    int low = 0;
    int high = n - 1;
    int mid = (low + high) / 2;
    
    while (low <= high)
    {
        if (values[mid] == value)
            return true;
        else if (value < values[mid])
        {
            high = mid - 1;
            mid = (low + high) / 2;
          // TODO
        }
        else if (value > values[mid])
        {
           low = mid + 1;
           mid = (low + high) / 2;
          // TODO
        }
        else 
            break;
    }
    return false;
}



/**
 * Sorts array of n values.
 */
 
void sort(int values[], int n)
{
    int i, j, min, tmp;
    
    for (i = 0; i < n - 1; i++) 
    {
        min = i;
        for (j = i + 1; j < n; j++) 
        {
            if (values[j] < values[min]) 
                min = j;
        }
        tmp = values[min];
        values[min] = values[i];
        values[i] = tmp;
    }
}
