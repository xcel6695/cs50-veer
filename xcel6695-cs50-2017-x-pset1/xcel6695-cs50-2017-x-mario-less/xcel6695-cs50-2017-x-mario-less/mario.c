#include <stdio.h>
#include <cs50.h>

int main(void) 
{
    printf("Height : ");
    int num = get_int();
    while (num < 0 || num > 23) 
    {
        printf("Height : ");
        num = get_int();
    }
    
    int max = num + 1;
    int tmp;
    int i = 0;
    int j = 0;
    
    for (i = 2; i <= max; i++) 
    {
        tmp = max - i;
        for (j = 1; j <= tmp; j++)
        {
            printf(" ");
        }
        tmp = max - tmp;
        for (j = 1; j <= tmp; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}