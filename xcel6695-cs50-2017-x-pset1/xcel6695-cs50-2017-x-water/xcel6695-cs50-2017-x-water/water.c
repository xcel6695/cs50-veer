#include <stdio.h>
#include <cs50.h>

int main(void) 
{
    int inp;
    int out;
    printf("Minutes: ");
    inp = get_int();
    out = inp * 12;
    printf("Bottles: %d\n", out);
}