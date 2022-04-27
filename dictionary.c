// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;
int count = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;
// Hash table
// N / 26 whole number = position of letter
struct node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int h = hash(word);
    count--;

    node *cursor = table[h];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor-> word, word) == 0)
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

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    count++;
    int dir1 = 0;
    int dir2 = 0;
    int dir = 0;

    if (strlen(word)>1 && (toupper(word[1]) - 'A' >= 0 && toupper(word[1]) - 'A' < 26))
    {
        dir1 = toupper(word[0]) - 'A';
        dir2 = toupper(word[1]) - 'A';
    }
    else if(strlen(word)>1)
    {
        dir1 = toupper(word[0]) - 'A';
        dir2 = toupper(word[2]) - 'A';
    }
    else
    {
        dir1 = toupper(word[0]) - 'A';
        dir2 = 0;
    }
    dir = dir1 * 26 + dir2;
        return dir;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (dictionary == NULL )
    {
        printf("File %s not found.\n", dictionary);
        return false;
    }
    char next_word[LENGTH + 1];

    while (fscanf(file, "%s", next_word) != EOF)
    {
        node *cursor = malloc(sizeof(node));
        if (cursor == NULL)
        {
            return false;
        }
        int h = hash(next_word);
        strcpy(cursor->word, next_word);

        cursor->next = table[h];
        table[h] = cursor;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    //printf("Size of dictionary is %i words\n",count);
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < N; i++)
    {
        node *cursor = table[i];

    // freeing linked lists
    while (cursor != NULL)
    {
        node *temp = cursor;
        cursor = cursor->next;
        free(temp);
    }
    }
    return true;
}
