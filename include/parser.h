#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <stdint.h>

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
    uint32_t    rd;
    uint32_t    rs1;
    uint32_t    rs2;
    uint32_t    imm;
} Instr;

typedef struct {
    Lexer l;
    Token current;
} Parser;

void parser_init(Parser* p, char* src);
Instr parser_next(Parser* p);

#endif
