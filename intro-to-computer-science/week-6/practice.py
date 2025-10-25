def main():
    my_list = []
    name = input("Enter your name: ")
    greeting = greet(name)
    print(greeting)
    print_greet = bool(
        input("Would you like to print out the Greeting Message again? (yes/no): ")
        .strip()
        .lower()
        == "yes"
    )
    if print_greet:
        print_char(greeting)

    while True:
        print("\n" + "-" * 40 + "\n")
        command = input("Enter a command (add, pop, show, exit): ").strip().lower()
        if command.startswith("add "):
            item = command[4:].strip()
            my_list = add_to_list(item, my_list)
            print(f'Added "{item}" to the list.')
        elif command.startswith("pop "):
            try:
                index = int(command[4:].strip())
                popped_item = pop_from_list(index, my_list)
                if popped_item is not None:
                    print(f'Removed "{popped_item}" from the list.')
                else:
                    print("Invalid index.")
            except ValueError:
                print("Please provide a valid index.")
        elif command == "show":
            print(show_list(my_list))
        elif command == "exit":
            print("Exiting the program.")
            break
        else:
            print("Unknown command. Please try again.")
    return "Program ended."


def greet(name):
    message = f"Hello, {name}!"
    instructions = cmd_instructions()
    return f"{message}\n{instructions}"


def print_char(phrase):
    for char in phrase:
        print(char)
    return "Done printing characters."


def add_to_list(item, lst=None):
    if lst is None:
        lst = []
    lst.append(item)
    return lst


def pop_from_list(index, lst):
    if 0 <= index < len(lst):
        return lst.pop(index)
    else:
        return None


def show_list(lst):
    # Return a nicely formatted ASCII table of the list items
    if not lst:
        return "The list is empty."
    table = "+------------------+\n"
    table += "| Index | Item  \n"
    for i, item in enumerate(lst):
        table += f"|  {i:<4} | {item:<5} \n"
    return table


def cmd_instructions():
    instructions = """
    Commands:
    1. add <item> - Add an item to the list
    2. pop <index> - Remove and return the item at the specified index
    3. show - Display the current list
    4. exit - Exit the program
    """
    return instructions


if __name__ == "__main__":
    main()
