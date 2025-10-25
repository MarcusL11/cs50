import csv
import sys


str_keys = []
database_list = []
longest_sequence = {}
sequence = None


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # TODO: Read database file into a variable
    with open(file=sys.argv[1], mode="r", newline="") as csvfile:
        reader = csv.DictReader(csvfile)
        str_keys = reader.fieldnames[1:]

        for row in reader:
            data = {"name": row["name"]}
            for key in str_keys:
                data[key] = int(row[key])
            database_list.append(data)

    # TODO: Read DNA sequence file into a variable
    with open(file=sys.argv[2], mode="r", newline="") as file:
        sequence = file.read()

    # TODO: Find longest match of each STR in DNA sequence
    for subsequence in str_keys:
        longest_sequence[subsequence] = longest_match(sequence, subsequence)

    # TODO: Check database for matching profiles

    match_count = 0
    matched_person = None

    for person in database_list:
        for key in str_keys:
            if person[key] == longest_sequence[key]:
                match_count += 1
        if match_count == len(str_keys):
            matched_person = person["name"]
            break
        else:
            match_count = 0
    if matched_person:
        print(matched_person)
    else:
        print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
