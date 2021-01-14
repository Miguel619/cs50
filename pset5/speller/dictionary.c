// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1]; // [word in dict]
    struct node *next;     // [node pointer]
    int tot;
}
node;

// Number of buckets in hash table
// one for every letter
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    /*
    return true if word in dictionary
    strcasecmp
    cursor -> first element
    compare
    cursor = cursor->next;
    compare .. etc
    */
   //hash to get value
    int key = hash(word);
    char dictWord[LENGTH + 1];
   // check list in hash
    for(node *tmp = table[key]; tmp != NULL; tmp = tmp->next){
        // traverse linked list looking for word strcasecmp
        strcpy(dictWord, tmp->word);
        if(strcasecmp(dictWord, word) == 0){
            return true;
        }
    }
    return false;
}

// Hashes word to a number
// consider using first 2 letters
unsigned int hash(const char *word)
{
    // Sorting hat
    //take strings and returns positive integer
    // % N first letter
    int key;
    
    key = tolower(word[0]) % 97;

    // return 0 - (n-1)
    return key;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    /*
    Takes in dictionary file we need to open and read
    Load into our hashtable
    HashTable:
    A -> apple -> angry
    B -> Banana -> Berry

    - Allocate mem for node
    node *n = malloc(sizeof(node));
    - Store the word hello in the word field of node n
    strcpy(n->word, "hello");
    - set net pointer to null
    n->next = NULL;
    */
    // open file (fopen && check null->false)

    FILE *dict = fopen(dictionary, "r");
    if(dict == NULL){
        return false;
    }
    // set head sizes to 0
    for(int h = 0; h < N; h++){
        node *head = malloc(sizeof(node));
        if(head == NULL){
            return false;
        }
        head->tot = 0;
        strcpy(head->word, "/");
        head->next = NULL;
        table[h] = head;
    }
    char dictWord[LENGTH + 1];
    node *n;
    //read strings one at a time (scanf(file, %s, word) && returns EOF)
    while(fscanf(dict, "%s", dictWord) != EOF){
        // create new node for each word (malloc/check NULL/strcpy)
        n = malloc(sizeof(node));
        if(n == NULL){
            return false;
        }
        // copy word to node
        strcpy(n->word, dictWord);

        // hash word to obtain bucket (hash(word))
        int key = hash(dictWord);
        // insert word in hash table in correct bucket
        n->next = table[key]->next;
        //set nodes in order (new node -> first element then head -> new node)
        table[key]->next = n;
        table[key]->tot++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // store size in the head
    int size = 0;
    for(int k = 0; k < N; k++){
        size += table[k]->tot;
    }
    return size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    /*
    cursor -> first item
    tmp = first item
    cursor = cursor->next;
    free(tmp)
    while(cursor->next != NULL)
    **/
    for(int h = 0; h < N; h++){
        while (table[h] != NULL){
            // set a tmp node to what we want to delete
            node *tmp = table[h]->next;
            // free the head
            free(table[h]);
            // set the head to tmp(the next node)
            table[h] = tmp;
        }
    }
    
    return true;
}