import re


class Parser:
    cnd = ["else if", "if", "else", "switch", "case"]
    loop = ["do", "while", "for"]

    def __init__(self, text):
        self.file_text = text

    def start(self):
        self.file_text = self.delete_extra_space(self.file_text)
        self.file_text = self.delete_comment(self.file_text)
        self.file_text = self.replace_condiction(self.file_text)
        self.file_text = self.replace_loop(self.file_text)

    def delete_extra_space(self, text):
        text = re.sub(r"\t+", r" ", text)
        text = re.sub(r" +", r" ", text)
        text = re.sub(r" +$", r"", text)
        text = re.sub(r"\n +", r"\n", text)
        return text

    def delete_comment(self, text):
        text = text.split("\n")
        preprocess_text = []
        for sentence in text:
            if not re.match(r"^#", sentence) and sentence:
                preprocess_text.append(sentence)
        return "\n".join(preprocess_text)

    def replace_condiction(self, text):
        for i in self.cnd:
            text = re.sub(i, "_cnd_", text)
        return text

    def replace_loop(self, text):
        for i in self.loop:
            text = re.sub(i, "_lop_", text)
        return text

    def get_str(self):
        return self.file_text


if __name__ == "__main__":
    f = open("expanded/101.cpp", "r").read()
    parser = Parser(f)
    parser.start()
    print(parser.get_str())
