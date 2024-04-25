import java.util.Scanner;
import java.util.Arrays;

public class PL4_java {
    public static int BUFFER_SIZE = 1024;
    
    //struct for equation
    public static class Sentence {
        String cur_char;
        String input;
        int cur_index = 0;
        int paren_count = 0;
    }
    
    //token to check types
    enum Token {
        NUMBER, LEFTPAREN, RIGHTPAREN, MULTIPLY, DIVIDE, PLUS, MINUS, UNKNOWN
    }
    
    //if token is relop
    enum Tkrelop {
        EQUAL, NOTEQUAL, ORMORE, ABOVE, ORLESS, UNDER, UNKNOWN2
    }
    
    //token cases
    public static Token word(String c) {
        switch (c.charAt(0)) {
            case '0':
                return Token.NUMBER;
            case '1':
                return Token.NUMBER;
            case'2':
                return Token.NUMBER;
            case'3':
                return Token.NUMBER;
            case'4': 
                return Token.NUMBER;
            case'5': 
                return Token.NUMBER;
            case'6': 
                return Token.NUMBER;
            case'7':
                return Token.NUMBER;
            case'8': 
                return Token.NUMBER;
            case'9': 
                return Token.NUMBER;
            case '(': 
                return Token.LEFTPAREN;
            case ')':
                return Token.RIGHTPAREN;
            case '*':
                return Token.MULTIPLY;
            case '/':
                return Token.DIVIDE;
            case '+':
                return Token.PLUS;
            case '-':
                return Token.MINUS;
            default:
                return Token.UNKNOWN;
        }
    }
    
    //token checking
    public static Token tkCheck(Sentence tmp) {
        String[] input = tmp.input.split("");
        if (tmp.cur_index < input.length){
            return word(input[tmp.cur_index]);
        }
        return Token.UNKNOWN;
    }
    
    //tkrelop cases
    public static Tkrelop word_relop(String a, String b) {
        switch (a.charAt(0)) {
            case '=':
                if (b.charAt(0) == '=') return Tkrelop.EQUAL;
                else return Tkrelop.UNKNOWN2;
            case '!':
                if (b.charAt(0) == '=') return Tkrelop.NOTEQUAL;
                else return Tkrelop.UNKNOWN2;
            case '<':
                if (b.charAt(0) == '=') return Tkrelop.ORLESS;
                else return Tkrelop.UNDER;
            case '>':
                if (b.charAt(0) == '=') return Tkrelop.ORMORE;
                else return Tkrelop.ABOVE;
            default:
                return Tkrelop.UNKNOWN2;
        }
    }
    
    //tkrelop checking
    public static Tkrelop tkrlpCheck(String a, String b) {
        return word_relop(a, b);
    }
    
    //prompt
    public static void prompt() {
        Scanner scanner = new Scanner(System.in);
    
        while (true) {
            System.out.print(">> ");
            String input = scanner.nextLine();
    
            if (input.equals("")) {
                break;
            }
    
            String[] inputArray = input.replaceAll("\\s+", "").split("");
            String inputWithoutWhitespace = String.join("", inputArray);
            Sentence stc = new Sentence();
            stc.cur_char = inputArray[0];
            stc.input = inputWithoutWhitespace;
            stc.cur_index = 0;
            stc.paren_count = 0;
            expr(stc);
        }
    
        scanner.close();
    }
    
    //syntax error check
    public static void error() {
        System.err.println(">> syntax error!!");
        prompt();
        System.exit(1);
    }
    
    //get next word
    public static void nextWord(Sentence tmp) {
        tmp.cur_index += 1;
        String[] input = tmp.input.split("");
        if (tmp.cur_index < input.length){
            tmp.cur_char = input[tmp.cur_index];
        }
    }
        
        // <expr> -> <bexpr> | <aexpr>
    public static int expr(Sentence stc) {
        boolean answer1;
        for (int i = 0; i < stc.input.length(); i++) {
            if (stc.input.charAt(i) == '=') {
                answer1 = bexpr(stc, i);
                if (answer1)
                    System.out.println(">> true");
                else
                    System.out.println(">> false");
                return 0;
            } else if (stc.input.charAt(i) == '<') {
                answer1 = bexpr(stc, i);
                if (answer1)
                    System.out.println(">> true");
                else
                    System.out.println(">> false");
                return 0;
            } else if (stc.input.charAt(i) == '>') {
                answer1 = bexpr(stc, i);
                if (answer1)
                    System.out.println(">> true");
                else
                    System.out.println(">> false");
                return 0;
            } else if (stc.input.charAt(i) == '!') {
                answer1 = bexpr(stc, i);
                if (answer1)
                    System.out.println(">> true");
                else
                    System.out.println(">> false");
                return 0;
            }
        }
        System.out.println(aexpr(stc));
        return 0;
    }
    
    //<bexpr> -> <aexpr> <relop> <aexpr>
    public static boolean bexpr(Sentence stc, int i) {
        String[] aexpr_array1 = new String[i];
        String[] stcinput = stc.input.split("");
        if(stc.input.isEmpty() || stc.cur_index >= stcinput.length){
            error();
            return false;
        }
        int left_stc, right_stc;
        int l = 0;
        
        stc.cur_char = stcinput[stc.cur_index];    
        
        for (int j = 0; j < i; j++) {
            aexpr_array1[j] = stcinput[j];
        }
        
        Sentence aexpr_stc1 = new Sentence();
        aexpr_stc1.cur_char = aexpr_array1[0];
        aexpr_stc1.input = String.join("", aexpr_array1);
        aexpr_stc1.cur_index = 0;
        aexpr_stc1.paren_count = 0;
        if (tkrlpCheck(stcinput[i], stcinput[i + 1]) == Tkrelop.EQUAL) {
            String[] aexpr_array2 = new String[stc.input.length() - (i+2)];
            for (int j = i + 2; j < stc.input.length(); j++) {
                aexpr_array2[l] = stcinput[j];
                l++;
            }
            Sentence aexpr_stc2 = new Sentence();
            aexpr_stc2.cur_char = aexpr_array2[0];
            aexpr_stc2.input = String.join("", aexpr_array2);
            aexpr_stc2.cur_index = 0;
            aexpr_stc2.paren_count = 0;
            
            left_stc = aexpr(aexpr_stc1);
            right_stc = aexpr(aexpr_stc2);
    
            return left_stc == right_stc;
        } else if (tkrlpCheck(stcinput[i], stcinput[i + 1]) == Tkrelop.NOTEQUAL) {
            String[] aexpr_array2 = new String[stc.input.length() - (i+2)];
            for (int j = i + 2; j < stc.input.length(); j++) {
                aexpr_array2[l] = stcinput[j];
                l++;
            }
            Sentence aexpr_stc2 = new Sentence();
            aexpr_stc2.cur_char = aexpr_array2[0];
            aexpr_stc2.input = String.join("", aexpr_array2);
            aexpr_stc2.cur_index = 0;
            aexpr_stc2.paren_count = 0;
            
            left_stc = aexpr(aexpr_stc1);
            right_stc = aexpr(aexpr_stc2);
    
            return left_stc != right_stc;
        } else if (tkrlpCheck(stcinput[i], stcinput[i + 1]) == Tkrelop.ORLESS) {
            String[] aexpr_array2 = new String[stc.input.length() - (i+2)];
            for (int j = i + 2; j < stc.input.length(); j++) {
                aexpr_array2[l] = stcinput[j];
                l++;
            }
            Sentence aexpr_stc2 = new Sentence();
            aexpr_stc2.cur_char = aexpr_array2[0];
            aexpr_stc2.input = String.join("", aexpr_array2);
            aexpr_stc2.cur_index = 0;
            aexpr_stc2.paren_count = 0;
            
            left_stc = aexpr(aexpr_stc1);
            right_stc = aexpr(aexpr_stc2);
    
            return left_stc <= right_stc;
        } else if (tkrlpCheck(stcinput[i], stcinput[i + 1]) == Tkrelop.UNDER) {
            String[] aexpr_array2 = new String[stc.input.length() - (i+1)];
            for (int j = i + 1; j < stc.input.length(); j++) {
                aexpr_array2[l] = stcinput[j];
                l++;
            }
            Sentence aexpr_stc2 = new Sentence();
            aexpr_stc2.cur_char = aexpr_array2[0];
            aexpr_stc2.input = String.join("", aexpr_array2);;
            aexpr_stc2.cur_index = 0;
            aexpr_stc2.paren_count = 0;
            
            left_stc = aexpr(aexpr_stc1);
            right_stc = aexpr(aexpr_stc2);
    
            return left_stc < right_stc;
        } else if (tkrlpCheck(stcinput[i], stcinput[i + 1]) == Tkrelop.ORMORE) {
            String[] aexpr_array2 = new String[stc.input.length() - (i+2)];
            for (int j = i + 2; j < stc.input.length(); j++) {
                aexpr_array2[l] = stcinput[j];
                l++;
            }
            Sentence aexpr_stc2 = new Sentence();
            aexpr_stc2.cur_char = aexpr_array2[0];
            aexpr_stc2.input = String.join("", aexpr_array2);
            aexpr_stc2.cur_index = 0;
            aexpr_stc2.paren_count = 0;
            
            left_stc = aexpr(aexpr_stc1);
            right_stc = aexpr(aexpr_stc2);
    
            return left_stc >= right_stc;
        }  else if (tkrlpCheck(stcinput[i], stcinput[i + 1]) == Tkrelop.ABOVE) {
            String[] aexpr_array2 = new String[stc.input.length() - (i+1)];
            for (int j = i + 1; j < stc.input.length(); j++) {
                aexpr_array2[l] = stcinput[j];
                l++;
            }
            Sentence aexpr_stc2 = new Sentence();
            aexpr_stc2.cur_char = aexpr_array2[0];
            aexpr_stc2.input = String.join("", aexpr_array2);
            aexpr_stc2.cur_index = 0;
            aexpr_stc2.paren_count = 0;
            
            left_stc = aexpr(aexpr_stc1);
            right_stc = aexpr(aexpr_stc2);
    
            return left_stc > right_stc;
        } else
            error();
        
        return false;
    }
    
    //<relop> -> == | != | < | > | <= | >=
    public static void relop(Sentence stc, int i, Tkrelop ptr) {
        String[] input = stc.input.split("");
        ptr = tkrlpCheck(input[i], input[i+1]);
    }
    
    //<aexpr> -> <term> {* <term> | / <term>}
    public static int aexpr(Sentence stc) {
        int _term = term(stc);
        while(true) {
          if(tkCheck(stc) == Token.MULTIPLY) {
              nextWord(stc);
              _term = _term * term(stc);
          } else if(tkCheck(stc) == Token.DIVIDE) {
              nextWord(stc);
              int i = term(stc);
              if(i == 0) {
                  System.err.println(">> division by zero");
                  prompt();
                  System.exit(1);
              }
              _term = _term / i;
          } else {
              return _term;
          }
       }
    }
    
    //<term> -> <factor> {+ <factor> | - <factor>}
    public static int term(Sentence stc) {
        int _factor = factor(stc);
        
        while(true) {
          if(tkCheck(stc) == Token.PLUS) {
              nextWord(stc);
              _factor = _factor + factor(stc);
          } else if(tkCheck(stc) == Token.MINUS) {
              nextWord(stc);
              _factor = _factor - factor(stc);
          } else {
              return _factor;
          }
        }
    }
    
    //<factor> -> <number> | (<aexpr>)
    public static int factor(Sentence stc) {
        int expression = 0;
        
        if(tkCheck(stc) == Token.NUMBER) {
            return numb(stc);
        } else if(tkCheck(stc) == Token.LEFTPAREN) {
            stc.paren_count = 1;
            nextWord(stc);
            expression = aexpr(stc);
            if(tkCheck(stc) != Token.RIGHTPAREN) {
                error();
            }
            nextWord(stc);
            stc.paren_count = 0;
            return expression;
        } else {
            error();
        }
        
        return 0;
    }
    
    //<number> -> <dec> {<dec>}
    public static int numb(Sentence stc) {
        int answer = 0;
        while(tkCheck(stc) == Token.NUMBER) {
            answer = answer * 10 + (stc.cur_char.charAt(0) - '0');
            nextWord(stc);
        }
        if(tkCheck(stc) == Token.LEFTPAREN) {
           error();
        } else if(tkCheck(stc) == Token.RIGHTPAREN && stc.paren_count == 0) {
            error();
        }
        return answer;
    }
        
        //main
    public static void main(String[] args) {
        prompt();
        
    }
}