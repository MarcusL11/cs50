from csv import DictReader
from cs50 import get_int


def main():
    min_temp = get_int("Max tempo: ")
    max_temp = get_int("Min tempo: ")

    playlist = []
    filename = "2018_top_100.csv"
    with open(filename) as file:
        file_reader = DictReader(file)
        for song in file_reader:
            if float(song["tempo"]) > min_temp and float(song["tempo"]) < max_temp:
                playlist.append(song)
            playlist.append(song)
    for song in playlist:
        print(f"{song['name']} at {song['tempo']} BPM")


if __name__ == "__main__":
    main()
