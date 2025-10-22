
// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Global variable to track the number of words loaded in the dictionary:
unsigned int words_count = 0;
bool dict_loaded = false;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get the hash value of the word as the index
    unsigned int index = hash(word);
    struct node *cursor = table[index];

    // Search the hash table at the location specified by the word’s hash value
    while (cursor != NULL){
        // compare using strcasecmp of the words
        if (strcasecmp(cursor->word, word) == 0){
            return true;
        }
        // move the temp pointer to the next node
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    // A polynomial rolling hash function
    // Choosing a base (a small prime number) and a modulus (usually the number of buckets, N).
    int base = 3;

    // Initialize a variable to store the sum of ASCII values.
    unsigned int hash = 0;

    // Loop through each character in the word.
    for (int i = 0; word[i] != '\0'; i++){
        // Convert the character to uppercase (if needed) and add its ASCII value to the sum.
        hash += toupper(word[i]);
    }

    // After the loop, use base and modular to finalized the hash
    hash =  ((hash * base) % N);
    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");

    if (source == NULL) {
        printf("The file did not open correctly.");
        // Update the dict_loaded tracker
        dict_loaded = false;
        return false;
    }

    // Update the dict_loaded tracker
    dict_loaded = true;
    printf("LOADED: %d\n", dict_loaded);


    // Reset the word counter
    if  (words_count != 0 ){
        words_count = 0;
    }

    // Create a buffer to temporarily store each word
    char word[LENGTH + 1];

    // Read each word in the file
    while (fscanf(source, "%s", word) == 1) {
        // Create space for a new hash table node
        node *new_node = malloc(sizeof(node));
        // Check if space was allocated successfully
        if (new_node == NULL) {
            fclose(source);
            return false;
        }
        // Copy the word into the new node
        strcpy(new_node->word, word);
        new_node->next = NULL;

        // Hash the word to obtain its hash value
        unsigned int index = hash(word);

        // Insert the new node into the hash table (using the index specified by its hash value)
        if (table[index] == NULL) {
            table[index] = new_node;
        } else {
            new_node->next = table[index];
            table[index] = new_node;
        }

        // Update the word counter
        words_count ++;
    }

    // Close the dictionary file
    fclose(source);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return  dict_loaded ? words_count: 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++) {
        node *cursor = table[i];
        while (cursor != NULL){
            // create another temp as a placeholder of the current node
            node *tmp = cursor;
            // move the current cursor to the next node
            cursor = cursor->next;
            // free the temp
            free(tmp);
        }
    }
    return true;
}

