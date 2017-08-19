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

string to_lower(string str, int code_len) 
{
    int i = 0;
    for (i = 0; i < code_len; i++) 
    {
        if (str[i] >= 65 && str[i] <= 90)
        {
            str[i] = str[i] + 32;
        }
    }
    return str;
}

int is_valid(string str, int len) 
{
    int i = 0;
    for (i = 0; i < len; i++) 
    {
        if (!isalpha(str[i]))
            return 0;
    }
    return 1;
}

int main(int argc, string argv[]) 
{
    while (argc != 2) 
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }
    
    string name, code;
    code = argv[1]; 
    int code_len, key, code_ind = 0, len;
    code_len = strlen(code);
    if (!is_valid(code, code_len))
    {
        printf("Only alphabets please\n");
        return 1;
    }
    code = to_lower(code, code_len);
    printf("plaintext: ");
    name = get_string();
    
    //printf("%s\n", code);
    len = strlen(name);
    printf("ciphertext: ");
    for (int i = 0; i < len; i++) 
    {
        if (isalpha(name[i])) 
        {
            key = code[code_ind] - 97;
            if (lower_case(name[i])) 
            {
                printf("%c", ((((name[i] - 97) + key) % 26) + 97));
            }
            else 
            {
                printf("%c", ((((name[i] - 65) + key) % 26) + 65));
            }
            code_ind++;
        
            if (code_ind == code_len)
                code_ind = 0;
        }
        else
        {
            printf("%c", name[i]);
        }
        
    }
    printf("\n");
    return 0;
}

