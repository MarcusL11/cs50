#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defining the node and the data structure
typedef struct node {
  string phrase;
  struct node *next;
} node;

#define LIST_SIZE 2

bool unload(node *list);
void visualizer(node *list);

int main(void)
{
  node *list = NULL;

  // Add items to list
  for (int i =0; i < LIST_SIZE; i++){
    string phrase = get_string("Enter a new phrase: ");

    // TODO: add phrase to new node in list
    node *n = malloc(sizeof(node));
    
    if (n == NULL){
      return 1;
    }

    n->phrase = phrase;
    n->next = list;
    list = n;
   
    // Visualize list after adding a node;
    visualizer(list);
  }
}

bool unload(node *list) {
  // TODO: Free all allocated nodes
  node *ptr = list;

  while (ptr != NULL) {
    ptr = list->next;
    free(list);
    list = ptr;
  }
  return false;
}

void visualizer(node *list) {
  while (list != NULL) {
    // Print the address of the node
    printf("-------------------------\n");
    printf("Address: %p \n", (void *)list);
    printf("Phrase: %s \n", list->phrase);
    printf("Next: %p \n", list->next);
    printf("-------------------------\n");
    list = list -> next;
  }
}


