#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void) 
{
    float change;
    printf("O hai! How much change is owed?\n");
    change = get_float();
    while (change < 0) 
    {
        printf("How much change is owed?\n");
        change = get_float();
    }
    
    change = change * 100;
    int cents = (int) round (change);
    
    int count = 0;
    if (cents >= 25) 
    {
        count = count + cents / 25;
        cents = cents% 25;
    }
    if (cents >= 10)
    {
        count = count + cents / 10;
        cents = cents % 10;
    }
    if (cents >= 5) 
    {
        count = count + cents / 5;
        cents = cents % 5;
    }
    if (cents >= 1) 
    {
        count = count + cents;
    }
    printf("%d\n", count);
}