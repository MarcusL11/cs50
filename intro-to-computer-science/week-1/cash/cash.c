
#include <cs50.h>
#include <stdio.h>

int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickles(int cents);
int calculate_pennies(int cents);

int main(void) {
  // Prompt the user for change owed, in cents
  int cents;
  int coins = 0;

  // Keep prompting user until they give a positive integer
  do {
    cents = get_int("Change owed: ");
  } while (cents < 0);

  // Calculate how many quarters you should give customer
  int quarters = calculate_quarters(cents);
  coins += quarters;

  // Subtract the value of those quarters from cents
  cents -= quarters * 25;

  // Calculate how many dimes you should give customer
  int dimes = calculate_dimes(cents);
  coins += dimes;

  // Subtract the value of those dimes from remaining cents
  cents -= dimes * 10;

  // Calculate how many nickels you should give customer
  int nickles = calculate_nickles(cents);
  coins += nickles;

  // Subtract the value of those nickels from remaining cents
  cents -= nickles * 5;

  // Calculate how many pennies you should give customer
  int pennies = calculate_pennies(cents);
  coins += pennies;

  // Subtract the value of those pennies from remaining cents
  cents -= pennies * 1;

  printf("Total coins: %i\n", coins);

  return 0;
}

int calculate_quarters(int cents) {
  int quarters = 0;
  while (cents >= 25) {
    quarters++;
    cents -= 25;
  }
  return quarters;
}

int calculate_dimes(int cents) {

  int dimes = 0;
  while (cents >= 10) {
    dimes++;
    cents -= 10;
  }
  return dimes;
}

int calculate_nickles(int cents) {

  int nickles = 0;
  while (cents >= 5) {
    nickles++;
    cents -= 5;
  }
  return nickles;
}

int calculate_pennies(int cents) {

  int pennies = 0;
  while (cents >= 1) {
    pennies++;
    cents -= 1;
  }
  return pennies;
}
