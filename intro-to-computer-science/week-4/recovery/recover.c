
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[]) {
  // Check that command-line argument is exactly one
  if (argc != 2) {
    printf("Useage: ./recover image\n");
    return 1;
  }

  // Open memory file
  FILE *memory_card_file = fopen(argv[1], "r");

  // Check if open successfully
  if (memory_card_file == NULL) {
    printf("Could not open file.\n");
    return 1;
  }

  // set buffer with block size of 512
  uint8_t buffer[BLOCK_SIZE];
  // Set img
  FILE *img = NULL;
  // Create array of 8 characters for file name
  char filename[8];
  // set counter for JPEG to name file
  int file_count = 0;

  // Create a while loop
  while (fread(buffer, sizeof(uint8_t), BLOCK_SIZE, memory_card_file) ==
         BLOCK_SIZE) {
    // Check if its a JPEG
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
        (buffer[3] & 0xf0) == 0xe0) {

      // Close any existing files
      if (img != NULL) {
        fclose(img);
      }

      // Create JPEG file with name
      sprintf(filename, "%03i.jpg", file_count++);
      img = fopen(filename, "w");

      // Write to JPEG file if one is open
      fwrite(buffer, sizeof(uint8_t), BLOCK_SIZE, img);
    } else {
      if (img != NULL) {
        // Continue writing to JPEG file if one is open
        fwrite(buffer, sizeof(uint8_t), BLOCK_SIZE, img);
      }
    }
  }

  // Close any remaining files
  if (img != NULL) {
    fclose(img);
  }

  fclose(memory_card_file);
  return 0;
}
