#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024

//struct for equation
typedef struct sentence {
	char cur_char;
	char *input;
	int cur_index;
	int paren_count;
} sentence;



//token to check types
enum token {NUMBER, LEFTPAREN, RIGHTPAREN, MULTIPLY, DIVIDE, PLUS, MINUS, UNKNOWN};

//token cases
enum token word(char c){
	switch(c){
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9': return NUMBER;
	case '(': return LEFTPAREN;
	case ')': return RIGHTPAREN;
	case '*': return MULTIPLY;
	case '/': return DIVIDE;
	case '+': return PLUS;
	case '-': return MINUS;
	default: return UNKNOWN;
	}
};

//token checking
enum token tkCheck(sentence *tmp)
{
	return word(tmp->input[tmp->cur_index]);
}

//if token is relop
enum tkrelop {EQUAL, NOTEQUAL, ORMORE, ABOVE, ORLESS, UNDER, UNKNOWN2};

//tkrelop cases
enum tkrelop word_relop(char a, char b){
	switch(a){
	case '=': if(b == '=') return EQUAL; else return UNKNOWN2;
	case '!': if(b == '=') return NOTEQUAL; else return UNKNOWN2;
	case '<': if(b == '=') return ORLESS; else return UNDER;
	case '>': if(b == '=') return ORMORE; else return ABOVE;
	default: return UNKNOWN2;
	}
};

//tkrelop checking
enum tkrelop tkrlpCheck(char a, char b)
{
	return word_relop(a, b);
}

//declaration
enum token tkCheck(sentence *tmp);
enum tkrelop tkrlpCheck(char a, char b);
void prompt();
void error();
void getNonBlank(char *input);
void nextWord(sentence *tmp);
int expr(sentence *stc);
bool bexpr(sentence *stc, int i);
void relop(sentence *stc, int i, char *ptr);
int aexpr(sentence *stc);
int term(sentence *stc);
int factor(sentence *stc);
int numb(sentence *stc);

//prompt
void prompt()
{
	while(1){
		char input[BUFFER_SIZE];

		printf(">> ");
		fgets(input, sizeof(input), stdin);

		if(strcmp(input, "\n") == 0)
			break;
		getNonBlank(input);
		sentence stc = {input[0], input, 0, 0};
		expr(&stc);
	}
}

//syntax error check
void error()
{
	fprintf(stderr, ">> syntax error!!\n");
	prompt();
	exit(1);
}

//getNonBlank => remove all the blank from input
void getNonBlank(char *input)
{
	char *temp = input;
	do {
		while(isspace(*temp))
			++temp;
		*input++ = *temp++;
	} while(*input != '\0');
}

//get next word
void nextWord(sentence *tmp)
{
	tmp->cur_index += 1;
	tmp->cur_char = tmp->input[tmp->cur_index];
}

//<expr> -> <bexpr> | <aexpr>
int expr(sentence *stc)
{
	bool answer1;
	for(unsigned int i = 0; i < strlen(stc->input)-1; i++){
		if(stc->input[i] == '='){
			answer1 = bexpr(stc, i);
			if(answer1)
				printf(">> true\n");
			else
				printf(">> false\n");
			return 0;
		}
		else if(stc->input[i] == '<'){
			answer1 = bexpr(stc, i);
			if(answer1)
				printf(">> true\n");
			else
				printf(">> false\n");
			return 0;
		}
		else if(stc->input[i] == '>'){
			answer1 = bexpr(stc, i);
			if(answer1)
				printf(">> true\n");
			else
				printf(">> false\n");
			return 0;
		}
		else if(stc->input[i] == '!'){
			answer1 = bexpr(stc, i);
			if(answer1)
				printf(">> true\n");
			else
				printf(">> false\n");
			return 0;
		}
	}
	printf("%d\n", aexpr(stc));
	return 0;
}
//<bexpr> -> <aexpr> <relop> <aexpr>
bool bexpr(sentence *stc, int i)
{
	char aexpr_array1[BUFFER_SIZE] = {0};
	char aexpr_array2[BUFFER_SIZE] = {0};
	int left_stc, right_stc;
	int l = 0;

	for(int j = 0; j < i; j++){
		aexpr_array1[j] = stc->input[j];
	}

	sentence aexpr_stc1 = {aexpr_array1[0], aexpr_array1, 0, 0};

	if(tkrlpCheck(stc->input[i], stc->input[i+1]) == EQUAL){
		for(unsigned int j = i+2; j < strlen(stc->input); j++){
			aexpr_array2[l] = stc->input[j];
			l++;
		}
		sentence aexpr_stc2 = {aexpr_array2[0], aexpr_array2, 0, 0};
		left_stc = aexpr(&aexpr_stc1);
		right_stc = aexpr(&aexpr_stc2);

		return left_stc == right_stc;
	}
	else if(tkrlpCheck(stc->input[i], stc->input[i+1]) == NOTEQUAL){
		for(unsigned int j = i+2; j < strlen(stc->input); j++){
			aexpr_array2[l] = stc->input[j];
			l++;
		}
		sentence aexpr_stc2 = {aexpr_array2[0], aexpr_array2, 0, 0};
		left_stc = aexpr(&aexpr_stc1);
		right_stc = aexpr(&aexpr_stc2);

		return left_stc != right_stc;
	}
	else if(tkrlpCheck(stc->input[i], stc->input[i+1]) == ORLESS){
		for(unsigned int j = i+2; j < strlen(stc->input); j++){
			aexpr_array2[l] = stc->input[j];
			l++;
		}
		sentence aexpr_stc2 = {aexpr_array2[0], aexpr_array2, 0, 0};
		left_stc = aexpr(&aexpr_stc1);
		right_stc = aexpr(&aexpr_stc2);

		return left_stc <= right_stc;
	}
	else if(tkrlpCheck(stc->input[i], stc->input[i+1]) == UNDER){
		for(unsigned int j = i+1; j < strlen(stc->input); j++){
			aexpr_array2[l] = stc->input[j];
			l++;
		}
		sentence aexpr_stc2 = {aexpr_array2[0], aexpr_array2, 0, 0};
		left_stc = aexpr(&aexpr_stc1);
		right_stc = aexpr(&aexpr_stc2);

		return left_stc < right_stc;
	}
	else if(tkrlpCheck(stc->input[i], stc->input[i+1]) == ORMORE){
		for(unsigned int j = i+2; j < strlen(stc->input); j++){
			aexpr_array2[l] = stc->input[j];
			l++;
		}
		sentence aexpr_stc2 = {aexpr_array2[0], aexpr_array2, 0, 0};
		left_stc = aexpr(&aexpr_stc1);
		right_stc = aexpr(&aexpr_stc2);

		return left_stc >= right_stc;
		}
	else if(tkrlpCheck(stc->input[i], stc->input[i+1]) == ABOVE){
		for(unsigned int j = i+1; j < strlen(stc->input); j++){
			aexpr_array2[l] = stc->input[j];
			l++;
		}
		sentence aexpr_stc2 = {aexpr_array2[0], aexpr_array2, 0, 0};
		left_stc = aexpr(&aexpr_stc1);
		right_stc = aexpr(&aexpr_stc2);

		return left_stc > right_stc;
	}
	else
		error();

	return 0;
}
//<relop> -> == | != | < | > | <= | >=
void relop(sentence *stc, int i, char *ptr)
{

	*ptr = tkrlpCheck(stc->input[i], stc->input[i+1]);
}
//<aexpr> -> <term> {* <term> | / <term>}
int aexpr(sentence *stc)
{
	int _term = term(stc);
	while(1)
	{
		if(tkCheck(stc) == MULTIPLY){
			nextWord(stc);
			_term = _term * term(stc);
		}
		else if(tkCheck(stc) == DIVIDE){
			nextWord(stc);
			int i = term(stc);
			if(i == 0){
				fprintf(stderr, ">> division by zero\n");
				prompt();
				exit(1);
			}
			_term = _term / i;
		}
		else return _term;
	}
}
//<term> -> <factor> {+ <factor> | - <factor>
int term(sentence *stc)
{
	int _factor = factor(stc);
	while(1)
	{
		if(tkCheck(stc) == PLUS){
			nextWord(stc);
			_factor = _factor + factor(stc);
		}
		else if(tkCheck(stc) == MINUS){
			nextWord(stc);
			_factor = _factor - factor(stc);
		}
		else return _factor;
	}
}
//<factor> -> <number> | (<aexpr>)
int factor(sentence *stc)
{
	int expression = 0;

	if(tkCheck(stc) == NUMBER)
		return numb(stc);
	else if(tkCheck(stc) == LEFTPAREN){
		stc->paren_count = 1;
		nextWord(stc);
		expression = aexpr(stc);
		if(tkCheck(stc) != RIGHTPAREN){
			error();
		}
		nextWord(stc);
		stc->paren_count = 0;
		return expression;
	}
	else{
		error();
	}
	return 0;
}
//<number> -> <dec> {<dec>}
int numb(sentence *stc)
{
	int answer = 0;
	while(tkCheck(stc) == NUMBER){
		answer = answer * 10 + (stc->cur_char - '0');
		nextWord(stc);
	}
	if(tkCheck(stc) == LEFTPAREN){
		error();
	}
	else if(tkCheck(stc) == RIGHTPAREN && !stc->paren_count){
		error();
	}
	return answer;
}
//main
int main()
{
	prompt();

	return 0;
}

