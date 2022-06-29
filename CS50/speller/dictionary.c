 // Implements a dictionary's functionality

#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
//no. of words in the dictionary
unsigned int word_count=0;


// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *cursor;
    unsigned int index=hash(word);
    if(index>=N)
    {
        return false;
    }
    cursor=table[index];

    for(cursor=table[index];cursor!=NULL;cursor=cursor->next)
    {
        if(strcasecmp(word,cursor->word)==0)
        {
            return true;
        }
    }

    return false;

}

// Hashes word to a number
unsigned int hash(const char *word)
{
/*    // TODO: Improve this hash function
    unsigned int Hash=0;
    for(int i=0;word[i]!='\0';i++)
    {
        Hash+=toupper(word[i]);
        Hash = (Hash*word[i])%N;
    }
    return Hash;
*/
    unsigned long hash = 5381;
    int c;
    while ((c = toupper(*word++)))
    {
        hash = ((hash << 5) + hash) + c;
        //hash * 33 + c
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //getting the hash index
    FILE *ptr=fopen(dictionary, "r");
    if (ptr == NULL)
    {
        return false;
    }
    char read_word[LENGTH+1];

    while(fscanf(ptr,"%s",read_word)!=EOF)
    {
        unsigned int index = hash(read_word);
        if(index>N)
        {
            return false;
        }
        //for the first word
        if(table[index]==NULL)
        {
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                return false;
            }
            //storing word in n
            strcpy(n->word,read_word);
            n->next=NULL;
            table[index]=n;
            word_count+=1;
        }
        //for the extra words added
        else
        {
            node *n = malloc(sizeof(node));
            //storing word in n
            strcpy(n->word,read_word);
            n->next=table[index];
            table[index]=n;
            word_count+=1;
        }
    }
    fclose(ptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if(word_count>0)
    {
        return word_count;
    }
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
        // Iterate through buckets
    for (int i = 0; i < N; i++)
    {
        // Set cursor to this each bucket location
        node *cursor = table[i];
// If cursor is not NULL, free
        while (cursor)
        {
            // Create temp
            node *tmp = cursor;
            // Move cursor to next node
            cursor = cursor->next;
            // Free up temp
            free(tmp);
        }
// If cursor is NULL
        if (i == N - 1 && cursor == NULL)
        {
            return true;
        }
    }
    return false;
}
