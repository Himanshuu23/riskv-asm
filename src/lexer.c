#include <ctype.h>
#include <string.h>
#include "lexer.h"

Token lexer_next(Lexer* l) {
    Token t;
    memset(&t, 0, sizeof(Token));
    t.line = l->line;

    while (1) {
        char c = l->text[l->current_position];

        if (c == '\0') {
            t.kind = END_OF_FILE;
            return t;
        }

        else if (c == ',') {
            t.kind = COMMAS;
            l->current_position++;
            return t;
        }
        
        else if (c == '\n') {
            t.kind = NEW_LINE;
            l->current_position++;
            return t;
        }

        else if (c == '(') {
            t.kind = LPARENTHESIS;
            l->current_position++;
            return t;
        }

        else if (c == ')') {
            t.kind = RPARENTHESIS;
            l->current_position++;
            return t;
        }

        else if (isalpha(c)) {
            int i = 0;
            char buf[64];
            while (isalpha(l->text[l->current_position]) || isdigit(l->text[l->current_position])) {
                buf[i] = l->text[l->current_position];
                i++; l->current_position++;
            }
            buf[i] = '\0';
            memcpy(t.text, buf, 64);
            t.kind = NAME;  

            return t;
        }
        
        else {
            l->current_position++;
        }
    } 
}
