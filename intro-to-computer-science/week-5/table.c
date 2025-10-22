#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  string phrase;
  struct node *next;
} node;

node *table[26];

int hash(string phrase);
bool unload(node *list);

int main(void) {
  // Add Items
  for (int i = 0; i < 3; i++) {
    string phrase = get_string("Enter a new phrase %i / 3: ", i + 1);
    // Find phrase bucket
    int bucket = hash(phrase);
    printf("%s hashes to %i\n", phrase, bucket);
  }
}

int hash(string phrase) {
  // returns a number from 0 to 25 base on the first letter of Phrase
  return tolower(phrase[0]) - 'a';
}
