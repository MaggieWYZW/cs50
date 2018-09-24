 // Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"
#include "hash.h"

// Node for linked list
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;
// Define a hashtable: array of nodes
static node *hashtable[HASHSIZE]; //hashtable size of 50

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //printf("------CHECK-------\n");
    //printf("word: %s \t", word);
    char tmp[strlen(word)+1];
    // convert the word into lower case
    for (int i=0; i < strlen(word); i++)
    {
        tmp[i] = tolower(word[i]);
    }
    tmp[strlen(word)] = '\0';

    node *cursor = hashtable[hash_djb2(&tmp[0])];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, &tmp[0])==0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
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
        // Create a new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        else
        {
            // Insert a word in the hashtable
            strcpy(new_node->word, word);
            if (hashtable[hash_djb2(&word[0])] == NULL)
            // the linked list is empty
            {
                new_node->next = NULL;
                hashtable[hash_djb2(&word[0])] = new_node;
            }
            else
            // the linked list is not empty
            {
                new_node->next = hashtable[hash_djb2(&word[0])];
                hashtable[hash_djb2(&word[0])] = new_node;
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
    for (int i=0; i < HASHSIZE; i++)
    {
        node *cursor = hashtable[i];
        while(cursor != NULL)
        {
            counter++;
            cursor = cursor->next;
        }
    }
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for(int i = 0; i < HASHSIZE; i++)
    {
        node *cursor = hashtable[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}



