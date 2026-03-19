#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/encoder.h"
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
    
    printf("%s\n", "Lexer's Output...");
    while (1) {
        Token t = lexer_next(&l);
        printf("%s: %s\n", kind_to_str(t.kind), t.text);
        if (t.kind == END_OF_FILE) break;
    }
    
    Parser p;
    parser_init(&p, "add x1, x2, x3\n");

    Instr instr = parser_next(&p);

    printf("\n");
    printf("%s\n", "Parser's Output...");
    printf("op = %d\n", instr.op);
    printf("rd: %d\n", instr.rd);
    printf("rs1: %d\n", instr.rs1);
    printf("rs2: %d\n", instr.rs2);

    uint32_t encoded = encode(instr);
    printf("\n");
    printf("%s\n", "Encoder's Output...");
    printf("0x%08x\n", encoded);

    return 0;
}
