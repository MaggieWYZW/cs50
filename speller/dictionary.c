 // Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Node for linked list
typedef struct node
{
    bool is_node;
    struct node *children[27];
}
node;
// Define a hashtable: array of nodes
node *root;

int index(char c)
{
    if (c < 'z' && c > 'a')
    {
        return (int) c-'a';
    }
    else if (c == '\'')
    {
        return 26;
    }
    else
    {
        return (int) c-'A';
    }
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE* file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Couldn't open dictionary! \n");
        return false;
    }

    //Load into a hash table
    // Scan dictionary word by word
    char word[LENGTH+1];
    while (fscanf(file, "%s", word) != EOF)
    {
        node *curser = root;
        // Create a new node
        for(int i = 0; i < strlen(word); i++)
        {
            if (curser == NULL)
            {
                node *new_node = malloc(sizeof(node));
                curser->children[index(word[i])] = new_node;
            }
            else if (curser->children[index(word[i])] == NULL && (i < strlen(word)-1))
            {
                node *new_node = malloc(sizeof(node));
                curser->children[index(word[i])] = new_node;
                curser = curser->children[index(word[i])];
            }
            else if ((i==strlen(word)-1) && curser->children[index(word[i])] == NULL)
            {
                node *new_node = malloc(sizeof(node));
                curser->children[index(word[i])] = new_node;
                curser->children[index(word[i])]->is_word = true;
            }
            else if (i==strlen(word)-1)
            {
                curser->is_word = true;
            }
            else
            {
                curser = curser->children[indes(word[i])];
            }
        }

    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // If the dictionary is not loaded, return 0
    int counter = 0;
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    return true;
}



