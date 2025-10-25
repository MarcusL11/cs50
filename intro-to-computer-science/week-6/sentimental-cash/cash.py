from cs50 import get_float


class Cash:
    def __init__(self, cent, coins):
        self.cent = cent
        self.coins = coins

    def calculate_coins(self, unit):
        print(f"Calculating for {unit}")

        count = 0

        while self.cent >= unit:
            print(f"Count: {count}")
            count += 1
            print(f"Starting cent: {self.cent}")
            self.cent -= unit
            print(f"Ending cent: {self.cent}")

        print(f"Starting Coins: {self.coins}")
        self.coins += count
        print(f"Ending Coins: {self.coins}")


if __name__ == "__main__":
    dollars = get_float("Change: ")
    while dollars < 0.01:
        dollars = get_float("Change must be greater than 0.01: ")

    cent = round(dollars * 100)
    cash = Cash(cent=cent, coins=0)
    cash.calculate_coins(25)
    cash.calculate_coins(10)
    cash.calculate_coins(5)
    cash.calculate_coins(1)
    print(f"Coins: {cash.coins}")
