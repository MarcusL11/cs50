#include <cs50.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, string argv[]) {
  // Check for usage, must be 2 CLA
  if (argc != 2) {
    printf("Please provide only one filename\n");
    return 1;
  }

  // Open File
  FILE *input = fopen(argv[1], "rb");

  if (input == NULL) {
    printf("Nothing in the file.");
    return 1;
  }

  // Create bugger for file
  uint8_t buffer[4];

  // Create an array of signature bytes
  uint8_t signature[] = {0x25, 0x50, 0x44, 0x46};

  // Ready first 4 bytes from the file
  size_t bytes_read = fread(buffer, sizeof(uint8_t), 4, input);
  if (bytes_read != 4) {
    printf("Could not read 4 bytes from file.\n");
    fclose(input);
    return 1;
  }

  // create the first 4 bytes again signaurue byte
  for (int i = 0; i < 4; i++) {
    if (signature[i] != buffer[i]) {
      printf("This is not a PDF!\n");
      return 0;
    }
  }

  // Success
  printf("This is a PDF!\n");

  // CLose the file
  fclose(input);
  return 0;
}
