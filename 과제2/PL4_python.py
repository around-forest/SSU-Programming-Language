import sys
import re

# struct for equation
class Sentence:
    def __init__(self):
        self.cur_char = ""
        self.input = ""
        self.cur_index = 0
        self.paren_count = 0

# token to check types
class Token:
    NUMBER, LEFTPAREN, RIGHTPAREN, MULTIPLY, DIVIDE, PLUS, MINUS, UNKNOWN = range(8)

# if token is relop
class Tkrelop:
    EQUAL, NOTEQUAL, ORMORE, ABOVE, ORLESS, UNDER, UNKNOWN2 = range(7)

# token cases
def word(c):
    switcher = {
        '0': Token.NUMBER,
        '1': Token.NUMBER,
        '2': Token.NUMBER,
        '3': Token.NUMBER,
        '4': Token.NUMBER,
        '5': Token.NUMBER,
        '6': Token.NUMBER,
        '7': Token.NUMBER,
        '8': Token.NUMBER,
        '9': Token.NUMBER,
        '(': Token.LEFTPAREN,
        ')': Token.RIGHTPAREN,
        '*': Token.MULTIPLY,
        '/': Token.DIVIDE,
        '+': Token.PLUS,
        '-': Token.MINUS,
    }
    return switcher.get(c, Token.UNKNOWN)

# token checking
def tkCheck(tmp):
    input_array = list(tmp.input)
    if tmp.cur_index < len(input_array):
        return word(input_array[tmp.cur_index])
    return Token.UNKNOWN

# tkrelop cases
def word_relop(a, b):
    switcher = {
        '=': Tkrelop.EQUAL if b == '=' else Tkrelop.UNKNOWN2,
        '!': Tkrelop.NOTEQUAL if b == '=' else Tkrelop.UNKNOWN2,
        '<': Tkrelop.ORLESS if b == '=' else Tkrelop.UNDER,
        '>': Tkrelop.ORMORE if b == '=' else Tkrelop.ABOVE,
    }
    return switcher.get(a, Tkrelop.UNKNOWN2)

# tkrelop checking
def tkrlpCheck(a, b):
    return word_relop(a, b)

# prompt
def prompt():
    while True:
        input_str = input(">> ")
        if input_str == "":
            break
        input_str = re.sub(r'\s', '', input_str)
        input_array = list(input_str)
        input_without_whitespace = "".join(input_array)
        stc = Sentence()
        stc.cur_char = input_array[0]
        stc.input = input_without_whitespace
        stc.cur_index = 0
        stc.paren_count = 0
        expr(stc)

# syntax error check
def error():
    print(">> syntax error!!")
    prompt()
    exit(1)

# get next word
def nextWord(tmp):
    tmp.cur_index += 1
    input_array = list(tmp.input)
    if tmp.cur_index < len(input_array):
        tmp.cur_char = input_array[tmp.cur_index]

def expr(stc):
    answer1 = False
    for i in range(len(stc.input)):
        if stc.input[i] == '=':
            answer1 = bexpr(stc, i)
            if answer1:
                print(">> true")
            else:
                print(">> false")
            return 0
        elif stc.input[i] == '<':
            answer1 = bexpr(stc, i)
            if answer1:
                print(">> true")
            else:
                print(">> false")
            return 0
        elif stc.input[i] == '>':
            answer1 = bexpr(stc, i)
            if answer1:
                print(">> true")
            else:
                print(">> false")
            return 0
        elif stc.input[i] == '!':
            answer1 = bexpr(stc, i)
            if answer1:
                print(">> true")
            else:
                print(">> false")
            return 0
    print(aexpr(stc))
    return 0

def bexpr(stc, i):
    aexpr_array1 = list(stc.input)[:i]
    stcinput = list(stc.input)
    if stc.input == "" or stc.cur_index >= len(stcinput):
        error()
        return False
    left_stc, right_stc = 0, 0
    l = 0

    stc.cur_char = stcinput[stc.cur_index]

    for j in range(i):
        aexpr_array1[j] = stcinput[j]

    aexpr_stc1 = Sentence()
    aexpr_stc1.cur_char = aexpr_array1[0]
    aexpr_stc1.input = "".join(aexpr_array1)
    aexpr_stc1.cur_index = 0
    aexpr_stc1.paren_count = 0
    if tkrlpCheck(stcinput[i], stcinput[i + 1]) == Tkrelop.EQUAL:
        aexpr_array2 = stcinput[i + 2:]
        aexpr_stc2 = Sentence()
        aexpr_stc2.cur_char = aexpr_array2[0]
        aexpr_stc2.input = "".join(aexpr_array2)
        aexpr_stc2.cur_index = 0
        aexpr_stc2.paren_count = 0

        left_stc = aexpr(aexpr_stc1)
        right_stc = aexpr(aexpr_stc2)

        return left_stc == right_stc
    elif tkrlpCheck(stcinput[i], stcinput[i + 1]) == Tkrelop.NOTEQUAL:
        aexpr_array2 = stcinput[i + 2:]
        aexpr_stc2 = Sentence()
        aexpr_stc2.cur_char = aexpr_array2[0]
        aexpr_stc2.input = "".join(aexpr_array2)
        aexpr_stc2.cur_index = 0
        aexpr_stc2.paren_count = 0

        left_stc = aexpr(aexpr_stc1)
        right_stc = aexpr(aexpr_stc2)

        return left_stc != right_stc
    elif tkrlpCheck(stcinput[i], stcinput[i + 1]) == Tkrelop.ORLESS:
        aexpr_array2 = stcinput[i + 2:]
        aexpr_stc2 = Sentence()
        aexpr_stc2.cur_char = aexpr_array2[0]
        aexpr_stc2.input = "".join(aexpr_array2)
        aexpr_stc2.cur_index = 0
        aexpr_stc2.paren_count = 0

        left_stc = aexpr(aexpr_stc1)
        right_stc = aexpr(aexpr_stc2)

        return left_stc <= right_stc
    elif tkrlpCheck(stcinput[i], stcinput[i + 1]) == Tkrelop.UNDER:
        aexpr_array2 = stcinput[i + 1:]
        aexpr_stc2 = Sentence()
        aexpr_stc2.cur_char = aexpr_array2[0]
        aexpr_stc2.input = "".join(aexpr_array2)
        aexpr_stc2.cur_index = 0
        aexpr_stc2.paren_count = 0

        left_stc = aexpr(aexpr_stc1)
        right_stc = aexpr(aexpr_stc2)

        return left_stc < right_stc
    elif tkrlpCheck(stcinput[i], stcinput[i + 1]) == Tkrelop.ORMORE:
        aexpr_array2 = stcinput[i + 2:]
        aexpr_stc2 = Sentence()
        aexpr_stc2.cur_char = aexpr_array2[0]
        aexpr_stc2.input = "".join(aexpr_array2)
        aexpr_stc2.cur_index = 0
        aexpr_stc2.paren_count = 0

        left_stc = aexpr(aexpr_stc1)
        right_stc = aexpr(aexpr_stc2)

        return left_stc >= right_stc
    elif tkrlpCheck(stcinput[i], stcinput[i + 1]) == Tkrelop.ABOVE:
        aexpr_array2 = stcinput[i + 1:]
        aexpr_stc2 = Sentence()
        aexpr_stc2.cur_char = aexpr_array2[0]
        aexpr_stc2.input = "".join(aexpr_array2)
        aexpr_stc2.cur_index = 0
        aexpr_stc2.paren_count = 0

        left_stc = aexpr(aexpr_stc1)
        right_stc = aexpr(aexpr_stc2)

        return left_stc > right_stc
    else:
        error();
    return 0;
    
# //<relop> -> == | != | < | > | <= | >=
def relop(stc, i, ptr):
    input = list(stc.input)
    ptr = tkrlpCheck(input[i], input[i+1])
    return ptr

# //<aexpr> -> <term> {* <term> | / <term>}
def aexpr(stc):
    _term = term(stc)
    while True:
        if tkCheck(stc) == Token.MULTIPLY:
            nextWord(stc)
            _term = _term * term(stc)
        elif tkCheck(stc) == Token.DIVIDE:
            nextWord(stc)
            i = term(stc)
            if i == 0:
                print(">> division by zero")
                prompt()
                sys.exit(1)
            _term = _term / i
        else:
            return _term

# //<term> -> <factor> {+ <factor> | - <factor>}
def term(stc):
    _factor = factor(stc)

    while True:
        if tkCheck(stc) == Token.PLUS:
            nextWord(stc)
            _factor = _factor + factor(stc)
        elif tkCheck(stc) == Token.MINUS:
            nextWord(stc)
            _factor = _factor - factor(stc)
        else:
            return _factor

# //<factor> -> <number> | (<aexpr>)
def factor(stc):
    expression = 0

    if tkCheck(stc) == Token.NUMBER:
        return numb(stc)
    elif tkCheck(stc) == Token.LEFTPAREN:
        stc.paren_count = 1
        nextWord(stc)
        expression = aexpr(stc)
        if tkCheck(stc) != Token.RIGHTPAREN:
            error()
        nextWord(stc)
        stc.paren_count = 0
        return expression
    else:
        error()

    return 0

# //<number> -> <dec> {<dec>}
def numb(stc):
    answer = 0
    while tkCheck(stc) == Token.NUMBER:
        answer = answer * 10 + (ord(stc.cur_char[0]) - ord('0'))
        nextWord(stc)
    if tkCheck(stc) == Token.LEFTPAREN:
        error()
    elif tkCheck(stc) == Token.RIGHTPAREN and stc.paren_count == 0:
        error()
    return answer

# main
def main(args):
    prompt()

if __name__ == "__main__":
    main(sys.argv[1:])
