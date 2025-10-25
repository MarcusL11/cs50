class Readability:
    def __init__(self, text):
        self.text = text
        self.sentences = self.count_sentences()
        self.words = self.count_words()
        self.letters = self.count_letters()
        self.index = self.coleman_liau_index()

    def count_sentences(self):
        sentences = 0
        for char in self.text:
            if char in ".!?":
                sentences += 1
        return sentences

    def count_words(self):
        words = self.text.split()
        return len(words)

    def count_letters(self):
        letters = 0
        # for each letter
        for i, char in enumerate(self.text):
            # check if its alpa
            if char.isalpha():
                letters += 1
            # check if surroundhyphen
            elif char == "-" and i > 0 and i < len(self.text) - 1:
                if self.text[i - 1].isalpha() and self.text[i + 1].isalpha():
                    letters += 1
        return letters

    def coleman_liau_index(self):
        L = self.letters / self.words * 100
        S = self.sentences / self.words * 100
        index = 0.0588 * L - 0.296 * S - 15.8
        return round(index)


if __name__ == "__main__":
    text = input("Text: ")
    readability = Readability(text)
    index = readability.index
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")
