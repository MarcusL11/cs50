# include <stdio.h>
# include <cs50.h>

// NOTES:
// AMEX 34 or 37
// AMEX is 15 digits long

// MASTERCARD 51, 52,  53, 54, 55
// MASTERCARD is 16 digits long

// VISA 4
// VISA is 13 or 16 digits long

// Prompt the user for the credit card number
int main(void) {
  // long cc_number = get_long("Input Credit Card Number: ");
  // use 4003600000000014 as example
  long cc_number = get_long("Input Credit Card Number: ");
  int sum = 0;
  long n;

  for (n = cc_number / 10; n > 0; n /= 100) {
    int digit = n % 10;
    int product = digit * 2;
    sum += (product / 10) + (product % 10);
  }

  for (n = cc_number; n > 0; n /= 100) {
    int digit = n % 10;
    sum += digit;
  }

  printf("Sum: %i\n", sum);

  // Is it a valid credit card number?
  if (sum % 10 == 0) { // checking if the card number ends with 0
    long first_two = cc_number;
    // get the first two digits checking 
    while (first_two >= 100) { // reduce the number until only the first two digits remain
      first_two /= 10;
    }

    int length = 0;
    long temp = cc_number;
    while (temp > 0) {
      temp /= 10; // remove the last digit of the cc number
      length++; // add to the length counter
    }

    // Check the card type based on the first two digits and length
    if ((first_two == 34 || first_two == 37) && length == 15) {
      printf("AMEX\n");
    } else if (first_two >= 51 && first_two <= 55 && length == 16) {
      printf("MASTERCARD\n");
    } else if ((first_two / 10 == 4) && (length == 13 || length == 16)) {
      printf("VISA\n");
    } else {
      printf("INVALID\n");
    }

  } else {
    printf("INVALID\n");
  }
}




