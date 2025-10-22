#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct person {
  struct person *parents[2];
  char alleles[2];
} person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void) {
  // Seed random number generator
  // strand(time(0));
  // Create a new family with three generations
  person *p = create_family(GENERATIONS);

  // Print family tree of blood types
  print_family(p, 0);

  // Free memory
  free_family(p);
}

// Create a new individual with generations
person *create_family(int generations) {

  // TODO: Allocate memory for new person
  person *new_person = malloc(sizeof(person));

  if (new_person == NULL) {
    // Returns Null and not 1 because we are not in main function and cannot
    // exit the program here
    return NULL;
  }

  // If there are still generations left to create
  if (generations > 1) {
    // Create two new parents for current person by recursively calling
    // create_family
    person *parent0 = create_family(generations - 1);
    person *parent1 = create_family(generations - 1);

    // TODO: Set parent pointers for current person
    new_person->parents[0] = parent0;
    new_person->parents[1] = parent1;

    // TODO: Randomly assign current person's alleles based on parents
    // By using a random function and modulo operator, you'll get either a 0 or
    // 1
    new_person->alleles[0] = parent0->alleles[rand() % 2];
    new_person->alleles[1] = parent1->alleles[rand() % 2];
  } else {
    // TODO: SEt parent points to NULL
    new_person->parents[0] = NULL;
    new_person->parents[1] = NULL;

    // TODO: Randomly assign alleles
    new_person->alleles[0] = random_allele();
    new_person->alleles[1] = random_allele();
  }
  return new_person;
}

char random_allele() {
  {
    int r = rand() % 3;
    if (r == 0) {
      return 'A';
    } else if (r == 1) {
      return 'B';
    } else {
      return 'O';
    }
  }
}

void free_family(person *p) {
  // TODO: Handle base case
  if (p == NULL) {
    return;
  }

  // TODO: Free parents recursively
  free_family(p->parents[0]);
  free_family(p->parents[1]);

  // TODO: Free Child
  free(p);
}

void print_family(person *p, int generation) {
  // Handle base case
  if (p == NULL) {
    return;
  }

  // Print indentation
  for (int i = 0; i < generation * INDENT_LENGTH; i++) {
    printf(" ");
  }

  // Print person
  printf("Generation %i, blood type %c%c\n", generation, p->alleles[0],
         p->alleles[1]);

  // Print parents of current person
  print_family(p->parents[0], generation + 1);
  print_family(p->parents[1], generation + 1);
}
