#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

typedef struct node
{
    struct node* nodes[27];
    bool word;
}node;

node* root;

unsigned int words;


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int length = strlen(word);

    node* ptr = root;

    for (int i=0; i < length; i++)
    {
        char c = tolower(word[i]);
        if (c == '\'')
        {
            c = 123;
        }
        struct node* nextNode = ptr->nodes[c-97];

        if (nextNode == NULL)
        {
            return false;
        }
        else
        {
            ptr = nextNode;
        }
    }
    if (ptr->word == true)
    {
        return true;
    }

    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }
    root = calloc(1, sizeof(node));
    node* ptr = root;
    for (char c = tolower(fgetc(dict)); c != EOF; c = fgetc(dict))
    {
        if (c == '\n')
        {
            if (ptr != root)
            {
                words++;
                ptr->word = true;
                ptr = root;
            }
        }
        else
        {
            if (c == '\'')
            {
                c = 123;
            }
            struct node* nextNode = ptr->nodes[c-97];
            if (nextNode == NULL)
            {
                ptr->nodes[c-97] = calloc(1, sizeof(node));
                ptr = ptr->nodes[c-97];
            }
            else
            {
                ptr = nextNode;
            }
        }
    }

    fclose(dict);

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return words;
}

/**
 * Recursive function that frees a trie from memory
 */
void clear(node* ptr)
{
    for (int i = 0; i < 27; i++)
    {
        if (ptr->nodes[i] != NULL)
        {
            clear(ptr->nodes[i]);
        }
    }

    free(ptr);
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    clear(root);
    return true;
}
