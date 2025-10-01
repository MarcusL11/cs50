#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, char *argv[]) {

  // prompt command-line for one argument 'k'.
  if (argc != 2) {
    printf("Usage: ./caesar key\n");
    return 1;
  }

  // check if argv[1] is only digits
  bool result = only_digits(argv[1]);

  // if not, print usage message and return 1
  if (!result) {
    printf("Usage: ./caesar key\n");
    return 1;
  }

  // convert argv[1] from string to int
  int k = atoi(argv[1]);

  // prompt user for plaintext
  string plaintext = get_string("plaintext:  ");

  // for each character in the plaintext:
  //    // Rotate the characfter if is_alpha
  printf("ciphertext: ");
  for (int i = 0; i < strlen(plaintext); i++) {
    char c = rotate(plaintext[i], k);
    printf("%c", c);
  }
  printf("\n");
}

bool only_digits(char str[]) {

  // strings are arrays of characters ending with null terminators '\0'
  for (int i = 0; str[i] != '\0'; i++) {
    if (!isdigit(str[i])) {
      return false;
    }
  }
  return true;
}

char rotate(char c, int n) {
  if (isalpha(c)) {
    if (islower(c)) {
      return (c - 'a' + n) % 26 + 'a';
    }
    if (isupper(c)) {
      return (c - 'A' + n) % 26 + 'A';
    }
  }
  return c;
}
