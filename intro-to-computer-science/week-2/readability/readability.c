#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int coleman_liau_index(int letters, int words, int sentences);
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void) {
  // prompt user for text
  string text = get_string("Text: ");

  // count the number of letters
  int letters = count_letters(text);

  // count the number of words
  int words = count_words(text);

  // count the number of sentences;
  int sentences = count_sentences(text);

  // compute the Coleman-liau index
  int index = coleman_liau_index(letters, words, sentences);
  // print the grade level

  if (index < 1) {
    printf("Before Grade 1\n");
  } else if (index >= 16) {
    printf("Grade 16+\n");
  } else {
    printf("Grade %i\n", index);
  }
}

int count_sentences(string text) {
  int sentences = 0;

  for (int i = 0, n = strlen(text); i < n; i++) {
    if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
      sentences++;
      printf("%c\n", text[i]);
    }
  }
  return sentences;
}

int count_words(string text) {
  int words = 1;

  for (int i = 0, n = strlen(text); i < n; i++) {
    if (text[i] == ' ') {
      words++;
    }
  }

  return words;
}

int count_letters(string text) {
  int letters = 0;

  for (int i = 0; i < strlen(text); i++) {
    if (isalpha(text[i])) {
      letters++;
    }
    // coount hyphens as part of a letter
    else if (text[i] == '-' && isalpha(text[i - 1]) && isalpha(text[i + 1])) {
      letters++;
    }
  }
  return letters;
}

int coleman_liau_index(int letters, int words, int sentences) {

  float L = 0;
  float S = 0;
  float index = 0;

  // find the average number of letters per 100 words in the text
  L = (letters / (float)words) * 100;

  // find the average number of sentences per 100 words in the text
  S = (sentences / (float)words) * 100;

  // Calculate the Coleman-Liau index
  index = 0.0588 * L - 0.296 * S - 15.8;

  // round the index to the nearest whole number
  index = round(index);

  return index;
}
