from cs50 import get_int


def main():
    # get the user's input for number of blocks
    height = 0
    min_height = 1
    max_height = 8

    height = get_int("Height: ")

    while height < min_height or height > max_height:
        height = get_int(f"Height must be between {min_height} - {max_height}: ")

    # Iterate throught the blocks to print in reverse with space
    for i in range(1, height + 1, 1):
        print_row(spaces=height - i, hashes=i)


def print_row(spaces: int, hashes: int):
    print(" " * spaces + "#" * hashes)


if __name__ == "__main__":
    main()
