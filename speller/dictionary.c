 // Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

#define ALPHABET_SIZE 27

// Node for trie
typedef struct node
{
    bool is_word;
    struct node *children[27];
}
node;

// Create a root node
static node *root;
int INDEX(char c);
node *createNode();
bool isLeaf(node *n);
bool unloadNode(node *n);

unsigned int word_count = 0;


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *curser = root;
    for (int i=0, wordl=strlen(word); i<wordl; i++)
    {
        int c_index = INDEX(word[i]);
        if (curser->children[c_index] != NULL)
        {
            curser = curser->children[c_index];
        }
        else
        {
            return false;
        }
    }
    return curser->is_word;
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

    //Load into a trie
    // Scan dictionary word by word, add to trie character by character
    char word[LENGTH+1];
    root = createNode();
    while (fscanf(file, "%s", word) != EOF)
    {
        node *curser = root;
        for(int i = 0, wordl=strlen(word); i < wordl; i++)
        {
            int c_index = INDEX(word[i]);
            if (curser->children[c_index] == NULL)  // character doesn't exist in children
            {
                node *new_node = createNode();
                if (new_node == NULL)  // error allocate new node
                {
                    unload();
                    return false;
                }
                // success allocate a new node
                curser->children[c_index] = new_node;
            }
            curser = curser->children[c_index];

        }
        curser->is_word = true;
        word_count++;
    }
    fclose(file);
    return true;
}




// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}


// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if (root == NULL)
    {
        return true;
    }
    return unloadNode(root);
}



// Create a new empty node
node *createNode()
{
    node *tmp = malloc(sizeof(node));
    if (tmp == NULL)
    {
        return NULL;
    }

    // set values
    tmp->is_word = false;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        tmp->children[i] = NULL;
    }
    return tmp;
}



// Compute the index of the character
int INDEX(const char c)
{
    const char ch = tolower(c);
    if (ch == '\'')
    {
        return ALPHABET_SIZE-1;
    }
    else
    {
        return (int)ch - (int)'a';
    }

}




bool unloadNode(node *curser)
{
    // for each node, check all children to be null
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
        if (curser->children[j] != NULL)
        {
            unloadNode(curser->children[j]);
        }
    }
    free(curser);
    return true;
}
