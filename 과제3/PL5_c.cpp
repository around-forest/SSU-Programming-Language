#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define BUFLEN 1024
#define TOKENLEN 100

// Token Classification
enum TokenType {
    TYPE, // which should be "int"
    VARIABLE, // var should be an alphabet
    EQUALS, // "=" for "<var> = <aexpr>"
    PLUS, // "+"
    MINUS, // "-"
    RLP_EQUALS, // "==" for bexpr
    RLP_ORMORE, // ">=" for bexpr
    RLP_ABOVE, // ">" for bexpr
    RLP_ORLESS, // "<=" for bexpr
    RLP_UNDER, // "<" for bexpr
    RLP_NOTEQUAL, // "!=" for bexpr
    LEFT_PAREN, // "(" for "while () {}"
    RIGHT_PAREN, // ")" for "while () {}"
    LEFT_BRACE, // "{" for "while () {}"
    RIGHT_BRACE, // "}" for "while () {}"
    WHILE, // "while" in <statement>
    PRINT, // "print" in <statement>
    NUMBER, // <dec>
    SEMICOLON, // ";" at the end of statement or aexpr
    END_OF_INPUT // end of input
};

// Structure for classified tokens
typedef struct Token {
    enum TokenType type; // TokenType
    char value[TOKENLEN]; // actual value from the input
} Token;

// Structure for <var>
typedef struct Variable {
    char name; // name of the variable
    int value; // value of the variable
} Variable;

// function declaration
void error();
void prompt();
void program(Token tokens[]);
void declaration(Token tokens[], Variable variables[], int *num_variables, int index);
void statement(Token tokens[], Variable variables[], int *num_variables, int *index);
int aexpr(Token tokens[], Variable variables[], int *num_variables, int *index);
int bexpr(Token tokens[], Variable variables[], int *num_variables, int *index);
int term(Token tokens[], Variable variables[], int *num_variables, int *index);
int number(Token tokens[], Variable variables[], int *num_variables, int *index);
int var(Token tokens[], Variable variables[], int *num_variables, int *index);

// function to classify the input by TokenType
void tokenize(char* input, Token tokens[]) {
    int i = 0;
    int j = 0;
    char current;

    while (input[i] != '\0') { // do it until the end of the input
        current = input[i]; // take an alphabet from the input

        // remove all the whitespace characters
        if (current == ' ' || current == '\n' || current == '\t') {
            i++;
            continue;
        }
        // semicolon
        else if (current == ';') {
            tokens[j].type = SEMICOLON;
            strcpy(tokens[j].value, ";"); // save the actual value of SEMICOLON type
            i++;
            j++;
            continue;
        }
        // left paren
        else if (current == '(') {
            tokens[j].type = LEFT_PAREN;
            strcpy(tokens[j].value, "(");
            i++;
            j++;
            continue;
        }
        // right paren
        else if (current == ')') {
            tokens[j].type = RIGHT_PAREN;
            strcpy(tokens[j].value, ")");
            i++;
            j++;
            continue;
        }
        // left brace
        else if (current == '{') {
            tokens[j].type = LEFT_BRACE;
            strcpy(tokens[j].value, "{");
            i++;
            j++;
            continue;
        }
        // right brace
        else if (current == '}') {
            tokens[j].type = RIGHT_BRACE;
            strcpy(tokens[j].value, "}");
            i++;
            j++;
            continue;
        }
        // relop equals
        else if (strncmp(&input[i], "==", 2) == 0) {
            tokens[j].type = RLP_EQUALS;
            strcpy(tokens[j].value, "==");
            i += 2;
            j++;
            continue;
        } 
        // relop ormore
        else if (strncmp(&input[i], ">=", 2) == 0) {
            tokens[j].type = RLP_ORMORE;
            strcpy(tokens[j].value, ">=");
            i += 2;
            j++;
            continue;
        } 
        // relop orless
        else if (strncmp(&input[i], "<=", 2) == 0) {
            tokens[j].type = RLP_ORLESS;
            strcpy(tokens[j].value, "<=");
            i += 2;
            j++;
            continue;
        } 
        // relop notequal
        else if (strncmp(&input[i], "!=", 2) == 0) {
            tokens[j].type = RLP_NOTEQUAL;
            strcpy(tokens[j].value, "!=");
            i += 2;
            j++;
            continue;
        } 
        // relop under
        else if (current == '<') {
            tokens[j].type = RLP_UNDER;
            strcpy(tokens[j].value, "<");
            i++;
            j++;
            continue;
        } 
        // relop above
        else if (current == '>') {
            tokens[j].type = RLP_ABOVE;
            strcpy(tokens[j].value, ">");
            i++;
            j++;
            continue;
        }
        // equals sign
        else if (current == '=') {
            tokens[j].type = EQUALS;
            strcpy(tokens[j].value, "=");
            i++;
            j++;
            continue;
        }
        // plus
        else if (current == '+') {
            tokens[j].type = PLUS;
            strcpy(tokens[j].value, "+");
            i++;
            j++;
            continue;
        }
        // minus
        else if (current == '-') {
            tokens[j].type = MINUS;
            strcpy(tokens[j].value, "-");
            i++;
            j++;
            continue;
        }
        // int type
        else if (strncmp(&input[i], "int", 3) == 0) {
            tokens[j].type = TYPE;
            strcpy(tokens[j].value, "int");
            i += 3;
            j++;
            continue;
        }
        // print statement
        else if (strncmp(&input[i], "print", 5) == 0) {
            tokens[j].type = PRINT;
            strcpy(tokens[j].value, "print");
            i += 5;
            j++;
            continue;
        }
        // while loop
        else if (strncmp(&input[i], "while", 5) == 0) {
            tokens[j].type = WHILE;
            strcpy(tokens[j].value, "while");
            i += 5;
            j++;
            continue;
        }
        // if variable starts with a letter, it's a variable name
        else if (islower(current)) {
            tokens[j].type = VARIABLE;
            tokens[j].value[0] = current;
            i++;
            j++;
            continue;
        }
        // if variable starts with a digit, it's a number
        else if (isdigit(current)) {
            tokens[j].type = NUMBER;
            tokens[j].value[0] = current;
            i++;
            j++;
            continue;
        }
        // error if no tokens match
        else
            error();
        // next alphabet
        i++;
    }
    // classify eof as END_OF_INPUT
    tokens[j].type = END_OF_INPUT;
    strcpy(tokens[j].value, "");
}
// main function
int main() {
    // call prompt
    prompt();
    
    return 0;
}
// prompt
void prompt() {
    char input[BUFLEN]; // input array
    struct Token tokens[BUFLEN]; // tokens array for the tokenized input
    int quit = 0; // check ouble "enter" to quit the program
    
    while(quit != 2){
        printf(">> "); // initial output
    
        fgets(input, BUFLEN, stdin); // get input from the user
        
        tokenize(input, tokens); // tokenize the input
        
        // quit program when "enter" is entered twice
        if(strcmp(input, "\n") == 0){
            quit++;
        }
        
        // start parser
        program(tokens);
    }
}
// function for error
void error() {
    printf(">> Syntax Error!\n"); // print error sentence
    prompt(); // restart prompt
    exit(1);
}

// <program> -> {<declaration>} {<statement>}
void program(Token tokens[]) {
    int index = 0; // **important** index for the tokenized array 
    int statement_check = false; // to check <declaration> after <statement>
    int num_tokens = 0; // number of tokens
    struct Variable variables[BUFLEN] = {0}; // array to save variable and it's value
    int num_variables = 0; // number of variables
    
    // get number of tokens
    while(tokens[num_tokens++].type != END_OF_INPUT);
    num_tokens--;
    
    for(index = 0; index <= num_tokens; index++){
        // call declaration
        if(tokens[index].type == TYPE && statement_check == false){
            declaration(tokens, variables, &num_variables, index);
            index += 2;
        }
        // declaration after statement
        else if(tokens[index].type == TYPE && statement_check == true){
            error();
        }
        
        // call statement if <var> = <aexpr> ;
        else if(tokens[index].type == VARIABLE){
            statement_check = true;
            statement(tokens, variables, &num_variables, &index);
        }
        
        // call statement if while (<bexpr>) { {<statement>} }
        else if(tokens[index].type == WHILE){
            statement_check = true;
            statement(tokens, variables, &num_variables, &index);
        }
        
        // call statement if print <aexpr> ;
        else if(tokens[index].type == PRINT){
            statement_check = true;
            statement(tokens, variables, &num_variables, &index);
        }
        // quit <program>
        else if(tokens[index].type == END_OF_INPUT){
            break;
        }
        else 
        	error();
        
    }
}

// <declaration> -> <type> <var> ;
void declaration(Token tokens[], Variable variables[], int *num_variables, int index) {
    if(tokens[index].type != TYPE) // type "int"
        error();
        
    if(tokens[index+1].type == VARIABLE){ // token type checking
        char name = tokens[index+1].value[0]; // get the real value of the VARIABLE
        variables[*num_variables].name = name; // save the name of the variable in the array for the variables
        variables[*num_variables].value = 0; // intial value of the variables
        (*num_variables)++; // increase the number of the variables
    }
    else // if it's not <var> after "int", error call
        error();
        
    if(tokens[index+2].type != SEMICOLON) // check SEMICOLON
        error(); // if not, error
}

// <statement> -> <var> = <aexpr> ; | while (<bexpr>) {{<statement>}} | print <aexpr> ;
void statement(Token tokens[], Variable variables[], int *num_variables, int *index) {
    // <statement> -> <var> = <aexpr> ;
    if(tokens[*index].type == VARIABLE){ // <var> checking
        if(tokens[*index+1].type != EQUALS){ // "=" checking after <var>
            error(); // if not, error
        }
        int var_check = false; // boolean to check whether the var is in the array for the variables
        char name = tokens[*index].value[0]; // get the name of the <var>
        *index += 2; // indexing
        for(int i = 0; i < *num_variables; i++){  // check whether the input <var> is already in the array for var
            if(variables[i].name == name){ // if it is, save the value
                variables[i].value = aexpr(tokens, variables, num_variables, index);
                var_check = true;
                break;
            }
        }
        if(var_check == false){ // if not, save the <var> name and it's value in the array
            variables[*num_variables].name = name;
            variables[*num_variables].value = aexpr(tokens, variables, num_variables, index);
            (*num_variables)++; // increase the number of the variables
        }
        if(tokens[*index].type == SEMICOLON); // SEMICOLON checking
        else
            error();
    }
    
    // while (<bexpr>) {{<statement>}}
    else if(tokens[*index].type == WHILE){
        int while_check = true; // boolean for the bexpr
        int while_index;
        int while_end = -1;
        if(tokens[*index+1].type != LEFT_PAREN){ // check "while ("
            error();
        }
        else{
            *index += 2; // indexing
            while_index = *index; // index of first token after "("
            while_check = bexpr(tokens, variables, num_variables, index); // call <bexpr>
            // after check relop, index is moved to ")"
            while(while_check){ // if the bexpr == TRUE
                if(tokens[*index].type == RIGHT_PAREN && tokens[*index+1].type == LEFT_BRACE){ // check "while () {"
                    *index += 2; // indexing
                    statement(tokens, variables, num_variables, index); // call statement for the first statement
                    // after statement, index is moved to ";"
                    while(tokens[*index+1].type != RIGHT_BRACE){ // if there are <statment>s, call the next <statement>
                        (*index)++;
                        statement(tokens, variables, num_variables, index);
                        // after statement, index is moved to next ";"
                    }
                    // after while, index is moved to last ";"
                    while_end = *index; // save the index of the last ";"
                    *index = while_index; // go back to bexpr
                }
                else{
                    error();
                }
                while_check = bexpr(tokens, variables, num_variables, index);
            }
            // if bexpr = FALSE, index is moved to ")" again. so, let index moves to last ";"
            if(while_end != -1){
                *index = while_end;
                (*index)++;
            }
            else{ // when nested "while" is inputted, it might occur some problem
	        	while(1){ // so check the number of "while" and the number of "}" between "(" and "}"
	                while(tokens[*index].type != RIGHT_BRACE){ // find the "}"
	                    (*index)++;
	                }
	                while_end = *index;
	        
		            int test = while_index;
		            int while_count = 0;
		            int rb_count = 0;
		            while(test < while_end){ // check the number of "while" and "}"
		            	if(tokens[test].type == WHILE){
		            		while_count++;
						} else if (tokens[test].type == RIGHT_BRACE){
							rb_count++;
						}
						test++;
					} // if they are not equal, find the next "}"
					if(while_count == rb_count){
						break;
					} else {
						(*index)++;
					}
				}
	        }
        }
    }
    
    // print <aexpr> ;
    else if(tokens[*index].type == PRINT){
        int result;
        
        (*index)++; // indexing
        
        result = aexpr(tokens, variables, num_variables, index); // call aexpr
        // after <aexpr>, index is moved to ";"
        if(tokens[*index].type == SEMICOLON){ // ";" checking
            // print <aexpr>    
            printf(">> %d\n", result);
        }
        else{
            error();
        }
    }
    
    else
    	error();
}

// <bexpr> -> <aexpr> <relop> <aexpr>
int bexpr(Token tokens[], Variable variables[], int *num_variables, int *index) {
    int left_value = 0;
    int right_value = 0;
    
    left_value = aexpr(tokens, variables, num_variables, index); // get the value of the LHS of the <relop>
        
    if(tokens[*index].type == RLP_ABOVE){ // <relop> checking ">"
        (*index)++; // indexing
        right_value = aexpr(tokens, variables, num_variables, index); // get the value of the RHS of the <relop>
        if(tokens[*index].type != RIGHT_PAREN)
        	error();
		if(left_value > right_value) // compare the two values
            return true;
        else
            return false;
    }
    else if(tokens[*index].type == RLP_UNDER){ // <relop> checking "<"
        (*index)++;
        right_value = aexpr(tokens, variables, num_variables, index);
        if(tokens[*index].type != RIGHT_PAREN)
        	error();
        if(left_value < right_value)
            return true;
        else
            return false;
    }
    else if(tokens[*index].type == RLP_NOTEQUAL){ // <relop> checking "!="
        (*index)++;
        right_value = aexpr(tokens, variables, num_variables, index);
        if(tokens[*index].type != RIGHT_PAREN)
        	error();
        if(left_value != right_value)
            return true;
        else
            return false;
    }
    else if(tokens[*index].type == RLP_ORLESS){ // <relop> checking "<="
        (*index)++;
        right_value = aexpr(tokens, variables, num_variables, index);
        if(tokens[*index].type != RIGHT_PAREN)
        	error();
        if(left_value <= right_value)
            return true;
        else
            return false;
    }
    else if(tokens[*index].type == RLP_ORMORE){ // <relop> checking ">="
        (*index)++;
        right_value = aexpr(tokens, variables, num_variables, index);
        if(tokens[*index].type != RIGHT_PAREN)
        	error();
        if(left_value >= right_value)
            return true;
        else
            return false;
    }
    else if(tokens[*index].type == RLP_EQUALS){ // <relop> checking "=="
        (*index)++;
        right_value = aexpr(tokens, variables, num_variables, index);
        if(tokens[*index].type != RIGHT_PAREN)
        	error();
        if(left_value == right_value)
            return true;
        else
            return false;
    }
    // when the user input "while (1 or 0)"
    else if(tokens[*index].type == RIGHT_PAREN){
        error();
    }
    else
    	error();
    
    return false;
}

// <aexpr> -> <term> {+ <term> | - <term>}
int aexpr(Token tokens[], Variable variables[], int *num_variables, int *index) {
    int _term = term(tokens, variables, num_variables, index); // call <term>
    while(1){ // <after first <term>, check whether the next token is "+" or "-"
        if(tokens[*index].type == PLUS){ // if "+"
            (*index)++;
            _term = _term + term(tokens, variables, num_variables, index); // equation for "+"
        }
        else if(tokens[*index].type == MINUS){ // if "-"
            (*index)++;
            _term = _term - term(tokens, variables, num_variables, index); // equation for "-"
        }
        else
            return _term; // return result of the term
    }
    return 0;
}
// <term> -> <number> | <var>
int term(Token tokens[], Variable variables[], int *num_variables, int *index) {
    int result = 0;
    
    if(tokens[*index].type == NUMBER) // token checking
        return number(tokens, variables, num_variables, index); // if <number>, call number func
    else if(tokens[*index].type == VARIABLE){ // if <var>
        return var(tokens, variables, num_variables, index); // call var func
    }
    else
        error();
    return 0;
}

// <number> -> <dec> {<dec>}
int number(Token tokens[], Variable variables[], int *num_variables, int *index) {
    int result = 0;
    while(tokens[*index].type == NUMBER){ // double checking the type of the token
        result = result * 10 + (tokens[*index].value[0] - '0'); // code to allow users to input double or more digits
        (*index)++; // indexing
    }
    return result; // return result
}

// <var> in <aexpr>
int var(Token tokens[], Variable variables[], int *num_variables, int *index) {
    if(tokens[*index].type == VARIABLE){ // type double checking
    	if(tokens[*index+1].type == VARIABLE){
    		error();
		}
        int var_check = false; // boolean to check whether the <var> is in the array for the variables
        char name = tokens[*index].value[0];
        for(int i = 0; i < *num_variables; i++){ // search the <var> from the array
            if(variables[i].name == name){ // if <var> is already saved in the array
                (*index)++;
                return variables[i].value; // return the value of the <var>
            }
        }
        if(var_check == false){ // if not, save in the array of the variables
            variables[*num_variables].name = name; // both name and,
            variables[*num_variables].value = 0; // the initial value 0
            (*num_variables)++; // increase the number of the variables
            (*index)++; // indexing
            return variables[*num_variables-1].value; // return the value of the <var> which should be 0
        }
    }
    
    return 0;
}

