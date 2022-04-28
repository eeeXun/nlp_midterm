import re
import nltk


class Parser:
    COND = ["else if", "if", "else", "switch", "case"]
    LOOP = ["do", "while", "for"]
    SYMBAL_TOKENS_C = ["...", "<<=", ">>=", "->*", "::", "*=", "/=", "%=",
                       "+=", "-=", "&=", "^=", "|=", "||", "&&", "==", "!=",
                       "<=", ">=", "<<", ">>", "++", "--", "->", ".*", "{",
                       "}", "[", "]", "(", ")", ":", ";", ",", "?", "=", "|",
                       "^", "&", "<", ">", "+", "-", "*", "/", "%", "~", "!",
                       "."]

    NORMAL_TOKENS_C = ["long long", "auto", "break", "catch", "char", "const",
                       "continue", "default", "delete", "double", "enum",
                       "extern", "float", "friend", "goto", "inline", "int",
                       "long", "new", "private", "protected", "public",
                       "redeclared", "register", "return", "short", "signed",
                       "sizeof", "static", "struct", "template", "this", "try",
                       "typedef", "union", "unsigned", "virtual", "void",
                       "volatile", "operator", "true", "false", "throw",
                       "NULL", "\\\\>", "cin", "cout", "printf", "scanf",
                       "begin", "end", "reverse", "puts", "min", "max",
                       "string", "_loop_", "_cond_"]

    def __init__(self, text, get_main=False):
        self.file_text = text
        self.word_tokens = []
        self.main_list = []
        self.tokens_count = {i: 0 for i in (
            self.SYMBAL_TOKENS_C + self.NORMAL_TOKENS_C)}
        self.get_main = get_main

    def start(self):
        self.file_text = self.delete_extra_space()
        self.file_text = self.delete_comment()
        self.word_tokens = self.word_tokenize()
        self.word_tokens = self.replace_condiction()
        self.word_tokens = self.replace_loop()
        if self.get_main:
            self.word_tokens = self.get_main_fun()
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

    def word_tokenize(self):
        text = self.file_text
        tokens = nltk.word_tokenize(text)

        # prevent "std::cout" to "std" ":" ":cout"
        for i in range(len(tokens)):
            if tokens[i] == ":" and tokens[i+1][0] == ":":
                tokens[i] += ":"
                tokens[i+1] = tokens[i+1][1:]
        return tokens

    def replace_condiction(self):
        tokens = self.word_tokens
        for i in range(len(tokens)):
            if tokens[i] in self.COND:
                tokens[i] = "_cond_"
        return tokens

    def replace_loop(self):
        tokens = self.word_tokens
        for i in range(len(tokens)):
            if tokens[i] in self.LOOP:
                tokens[i] = "_loop_"
        return tokens

    def get_main_fun(self):
        vectors = {}
        main_list = []
        tokens = self.word_tokens
        for i in range(len(tokens)):
            if tokens[i] in vectors:
                vectors[tokens[i]] += 1
            else:
                vectors[tokens[i]] = 1
            if tokens[i] == "main" and tokens[i+1] == "(":
                count = 0
                flag = 0
                for j in range(i+3, len(tokens)):
                    main_list.append(tokens[j])
                    if tokens[j] == "{":
                        count += 1
                        flag = 1
                    if tokens[j] == "}":
                        count -= 1
                    if count == 0 and flag == 1:
                        break
        main_list = main_list[1:-1]
        return main_list

    def get_tokens_count(self):
        for token in self.word_tokens:
            for token_c in self.SYMBAL_TOKENS_C:
                tmp = "\\".join(list(token_c))
                symbal_pattern = r"(\w)*\{}(\w)*".format(tmp)
                if re.match(symbal_pattern, token):
                    self.tokens_count[token_c] += 1
                    break
            for token_c in self.NORMAL_TOKENS_C:
                normal_pattern = r"(\W)*{}(\W)*".format(token_c)
                if re.match(normal_pattern, token):
                    self.tokens_count[token_c] += 1
                    break

    def get_str(self):
        return " ".join(self.word_tokens)

    def get_tokens(self):
        return self.tokens_count


if __name__ == "__main__":
    nltk.download("punkt", "./venv/nltk_data")
    nltk.download("book", "./venv/nltk_data")
    f = open("expanded/98.cpp", "r").read()
    parser = Parser(f, get_main=True)
    parser.start()
    # print(parser.get_tokens())
    print(len(parser.get_tokens()))
    del parser
    # print(parser.get_str())
