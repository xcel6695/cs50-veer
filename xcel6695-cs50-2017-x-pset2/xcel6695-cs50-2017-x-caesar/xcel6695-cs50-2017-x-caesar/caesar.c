#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int lower_case(char a) 
{
    if (a >= 97 && a <= 122) 
        return 1;
    else 
        return 0;
}

int main(int argc, string argv[]) 
{
    while (argc != 2) 
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
    string name;
    printf("plaintext: ");
    name = get_string();
    int key = atoi(argv[1]);
    //char tmp;
    
    int len = strlen(name);
    printf("ciphertext: ");
    for (int i = 0; i < len; i++) 
    {
        if (isalpha(name[i])) 
        { 
            if (lower_case(name[i])) 
            {
                printf("%c", ((((name[i] - 97) + key) % 26) + 97));
            }
            else 
            {
                printf("%c", ((((name[i] - 65) + key) % 26) + 65));
            }
        }
        else
        {
            printf("%c", name[i]);
        }
    }
    printf("\n");
    return 0;
}

