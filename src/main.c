#include "lexer.h"
#include <stdio.h>

const char* kind_to_str(TokenKind k) {
    switch(k) {
        case NAME:              return "NAME";
        case COMMAS:            return "COMMAS";
        case NEW_LINE:          return "NEWLINE";
        case END_OF_FILE:       return "EOF";
        case LPARENTHESIS:      return "LEFTPARENTHESIS";
        case RPARENTHESIS:      return "RIGHTPARENTHESIS";
        case NUM:               return "NUMBER";
        
        default:                return "UNKNOWN";
    } 
}

int main() {
    Lexer l;
    l.text              = "add x1, x2, x3\n";
    l.current_position  = 0;
    l.line              = 1;

    while (1) {
        Token t = lexer_next(&l);
        printf("%s: %s\n", kind_to_str(t.kind), t.text);
        if (t.kind == END_OF_FILE) break;
    }

    return 0;
}
