
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct {
  int winner;
  int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[]) {
  // Check for invalid usage
  if (argc < 2) {
    printf("Usage: tideman [candidate ...]\n");
    return 1;
  }

  // Populate array of candidates
  candidate_count = argc - 1;
  if (candidate_count > MAX) {
    printf("Maximum number of candidates is %i\n", MAX);
    return 2;
  }
  for (int i = 0; i < candidate_count; i++) {
    candidates[i] = argv[i + 1];
  }

  // Clear graph of locked in pairs
  for (int i = 0; i < candidate_count; i++) {
    for (int j = 0; j < candidate_count; j++) {
      locked[i][j] = false;
    }
  }

  pair_count = 0;
  int voter_count = get_int("Number of voters: ");

  // Query for votes
  for (int i = 0; i < voter_count; i++) {
    // ranks[i] is voter's ith preference
    int ranks[candidate_count];

    // Query for each rank
    for (int j = 0; j < candidate_count; j++) {
      string name = get_string("Rank %i: ", j + 1);

      if (!vote(j, name, ranks)) {
        printf("Invalid vote.\n");
        return 3;
      }
    }

    record_preferences(ranks);

    printf("\n");
  }

  add_pairs();
  sort_pairs();
  lock_pairs();
  print_winner();
  return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[]) {
  // TODO
  // Look for a candidate called name
  // If candidate found, update ranks and return true. ranks[i] is the voter's
  // ith preference. if no candidate found, don't update any ranks and return
  // false.
  for (int i = 0; i < candidate_count; i++) {
    if (strcmp(name, candidates[i]) == 0) {
      ranks[rank] = i;
      return true;
    }
  }
  return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[]) {
  // TODO
  // Update the prefrences array based on the current voter's ranks
  for (int i = 0; i < candidate_count; i++) {
    for (int j = i + 1; j < candidate_count; j++) {
      preferences[ranks[i]][ranks[j]]++;
    }
  }
  return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void) {
  // TODO
  // Add each pair of candidates to pairs array if one candidate is preferred
  // over the other. Update global variable pair_count to be the total number of
  // pairs.
  for (int i = 0; i < candidate_count; i++) {
    for (int j = i + 1; j < candidate_count; j++) {
      // scenario 1
      if (preferences[i][j] > preferences[j][i]) {
        pairs[pair_count].winner = i;
        pairs[pair_count].loser = j;
        pair_count++;
      }
      // scenario 2
      else if (preferences[i][j] < preferences[j][i]) {
        pairs[pair_count].winner = j;
        pairs[pair_count].loser = i;
        pair_count++;
      }
    }
  }
  return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void) {
  // TODO
  // Sort pairs in order by decreasing strength of victory.
  // Using selection sort algorithm
  for (int i = 0; i < pair_count; i++) {
    for (int j = i + 1; j < pair_count; j++) {
      int strenght_0 = preferences[pairs[i].winner][pairs[i].loser] -
                       preferences[pairs[i].loser][pairs[i].winner];
      int strength_1 = preferences[pairs[j].winner][pairs[j].loser] -
                       preferences[pairs[j].loser][pairs[j].winner];
      if (strenght_0 < strength_1) {
        pair temp = pairs[i];
        pairs[i] = pairs[j];
        pairs[j] = temp;
      }
    }
  }
  return;
}

// Recursive function checking if locking a pair creates a cycle
bool causes_cycle(int start, int end) {
  if (end == start) {
    return true;
  }
  for (int i = 0; i < candidate_count; i++) {
    if (locked[end][i]) {
      if (causes_cycle(start, i)) {
        return true;
      }
    }
  }
  return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void) {
  // TODO
  // Update locked to create the locked graph by adding all edgeds in
  // decreasing order of victory strength, as long as there is no cycle.
  for (int i = 0; i < pair_count; i++) {
    if (!causes_cycle(pairs[i].winner, pairs[i].loser)) {
      locked[pairs[i].winner][pairs[i].loser] = true;
    }
  }
  return;
}

// Print the winner of the election
void print_winner(void) {
  // TODO
  // Print out the winner of the election, who will be the source of the
  // graph. You may assume there will not be more than one source.
  for (int i = 0; i < candidate_count; i++) {
    bool has_edge = false;
    for (int j = 0; j < candidate_count; j++) {
      if (locked[j][i]) {
        has_edge = true;
        break;
      }
    }
    if (!has_edge) {
      printf("%s\n", candidates[i]);
      return;
    }
  }
  return;
}

// a ranked-choice voting method that’s guaranteed to produce the Condorcet
// winner of the election if one exists. In a file called tideman.c in a
// folder called tideman, create a program to simulate an election by the
// Tideman voting method.
