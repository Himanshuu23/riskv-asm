#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef enum {
    ADD,
    SUB,
    ADDI,
    LW,
    SW,
    BEQ,
    JAL,
    RET,
} OpKind;

typedef struct {
    OpKind op;
    int    rd;
    int    rs1;
    int    rs2;
    int    imm;
} Instr;

typedef struct {
    Lexer l;
    Token current;
} Parser;

void parser_init(Parser* p, char* src);
Instr parser_next(Parser* p);

#endif
