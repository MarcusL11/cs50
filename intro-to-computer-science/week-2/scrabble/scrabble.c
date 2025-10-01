#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int POINTS[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int calculate_score(string word);

int main(void) {
  int score_1 = 0;
  int score_2 = 0;

  // Prompt the user for 2 words
  string word_1 = get_string("Player 1: ");
  string word_2 = get_string("Player 2: ");

  // Compute the score for each word
  score_1 = calculate_score(word_1);
  printf("Score 1: %i\n", score_1);
  score_2 = calculate_score(word_2);
  printf("Score 2: %i\n", score_2);

  // Print the winner
  if (score_1 > score_2) {
    printf("Player 1 wins!\n");
  } else if (score_2 > score_1) {
    printf("Player 2 wins!\n");
  } else {
    printf("Tie!\n");
  }
}

// compute function
int calculate_score(string word) {
  // Initialize score variable
  int score = 0;

  // loop through the POINTS array and add score for each letter
  for (int i = 0; i < strlen(word); i++) {
    if (isupper(word[i])) {
      score += POINTS[word[i] - 'A'];
    } else if (islower(word[i])) {
      score += POINTS[word[i] - 'a'];
    } else if (isalpha(word[i])) {
      score += 0;
    }
  }
  return score;
}
