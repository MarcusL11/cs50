
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_alpha(string s);
char substitute(char c, char *key);

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("Usage: ./caesar key\n");
    return 1;
  }

  bool result = only_alpha(argv[1]);

  if (!result) {
    printf("Usage: ./caesar key\n");
    return 1;
  }

  if (strlen(argv[1]) != 26) {
    printf("Key must be 26 characters.\n");
    return 1;
  }

  char *key = argv[1];

  for (int i = 0; i < 26; i++) {
    for (int j = i + 1; j < 26; j++) {
      if (tolower(key[i]) == tolower(key[j])) {
        printf("Key must not contain duplicate characters.\n");
        return 1;
      }
    }
  }

  // prompt user for plaintext
  string plaintext = get_string("plaintext:  ");

  printf("ciphertext: ");

  for (int i = 0; i < strlen(plaintext); i++) {
    char c = substitute(plaintext[i], key);
    printf("%c", c);
  }
  printf("\n");
}

bool only_alpha(char str[]) {

  // strings are arrays of characters ending with null terminators '\0'
  for (int i = 0; str[i] != '\0'; i++) {
    if (!isalpha(str[i])) {
      return false;
    }
  }
  return true;
}

char substitute(char c, char *key) {
  if (isupper(c)) {
    return toupper(key[c - 'A']);
  } else if (islower(c)) {
    return tolower(key[c - 'a']);
  } else {
    return c;
  }
}
