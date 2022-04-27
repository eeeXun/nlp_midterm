import re


class Parser:
    cond = ["else if", "if", "else", "switch", "case"]
    loop = ["do", "while", "for"]
    TOKENS = ["{", "}", "[", "]", "(", ")", "::", ":", ";", ",", "?", "...",
              "=", "*=", "/=", "%=", "+=", "-=", "<<=", ">>=", "&=", "^=",
              "|=", "||", "&&", "|", "^", "&", "==", "!=", "<", ">", "<=",
              ">=", "<<", ">>", "+", "-", "*", "/", "%", "++", "--", "~", "!",
              ".", "->", ".*", "->*", "auto", "break", "catch", "char",
              "const", "continue", "default", "delete", "double", "enum",
              "extern", "float", "friend", "goto", "inline", "int", "long",
              "new", "private", "protected", "public", "redeclared",
              "register", "return", "short", "signed", "sizeof", "static",
              "struct", ":", "template", "this", "try", "typedef", "union",
              "unsigned", "virtual", "void", "volatile", "operator",
              "true", "false", "throw", "NULL", "\\\\>", "cin", "cout",
              "printf", "scanf", "begin", "end", "reverse", "puts", "min",
              "max", "string", "_loop_", "_cond_"]

    def __init__(self, text):
        self.file_text = text
        self.tokens_count = {i: 0 for i in self.TOKENS}

    def start(self):
        self.file_text = self.delete_extra_space()
        self.file_text = self.delete_comment()
        self.file_text = self.replace_condiction()
        self.file_text = self.replace_loop()
        self.get_tokens_count()

    def delete_extra_space(self):
        text = self.file_text
        text = re.sub(r"\t+", r" ", text)
        text = re.sub(r" +", r" ", text)
        text = re.sub(r" +$", r"", text)
        text = re.sub(r"\n +", r"\n", text)
        return text

    def delete_comment(self):
        text = self.file_text.split("\n")
        preprocess_text = []
        for sentence in text:
            if not re.match(r"^#", sentence) and sentence:
                preprocess_text.append(sentence)
        return "\n".join(preprocess_text)

    def replace_condiction(self):
        text = self.file_text
        for i in self.cond:
            text = re.sub(i, "_cond_", text)
        return text

    def replace_loop(self):
        text = self.file_text
        for i in self.loop:
            text = re.sub(i, "_loop_", text)
        return text

    def get_tokens_count(self):
        for token in self.TOKENS:
            self.tokens_count[token] = self.file_text.count(token)

    def get_str(self):
        return self.file_text

    def get_tokens(self):
        return self.tokens_count


if __name__ == "__main__":
    f = open("expanded/0.cpp", "r").read()
    parser = Parser(f)
    parser.start()
    print(parser.get_tokens())
