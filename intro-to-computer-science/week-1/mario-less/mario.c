#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


void print_row( int spaces, int hashes);

int main(void)
{
  int height;
  do
  {
      height = get_int("Height must be between 1 and 8, please try again: ");
  }
  while (height < 1);

  // call the print_row function for the number of times of th user's input
  for (int i = 1; i <= height; i++)
  // Logic:  This prints our each row of the pyramid.
  {
    print_row(height - i, i);
  }
}


void print_row(int spaces, int hashes)
{
  // Delcare the characters to be printed
  char space = ' ';
  char hash = '#';

  for (int j = 0; j < spaces; j++)
  // Logic: iterate the number of times where spaces is > 0 but < height
  // Because the last row will have 0 space and all hashes., so we EXCLUDE the height.
  {
    printf("%c", space);
  }
  for (int j = 0; j < hashes; j++)
  // Lofic: iterate the number of times where hashes is > 0 but <= height
  // Because the last row will have all hashes and no spaces, so we INCLUDE the height.
  {
    printf("%c", hash);
  }
  // print a new line after each row
  printf("\n");
}

