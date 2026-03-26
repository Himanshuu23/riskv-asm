#include "../include/parser.h"
#include <stdlib.h>
#include <string.h>

int reg_num(char* r) {
    return atoi(r + 1);
}

void advance(Parser* p) {
    p->current = lexer_next(&p->l);
}

void parser_init(Parser* p, char* src) {
    p->l.text = src;
    p->l.current_position = 0;
    p->l.line = 1;

    p->current = lexer_next(&p->l);
}

Instr parser_next(Parser *p) {
    Instr instr;
    memset(&instr, 0, sizeof(Instr)); 

    if (strcmp(p->current.text, "add") == 0) {
        instr.op = ADD;
        advance(p);
        instr.rd = reg_num(p->current.text);
        advance(p);
        advance(p);
        instr.rs1 = reg_num(p->current.text);
        advance(p);
        advance(p);
        instr.rs2 = reg_num(p->current.text);
        advance(p);
        return instr;
    }

    else if (strcmp(p->current.text, "sub") == 0) {
        instr.op = SUB;
        advance(p);
        instr.rd = reg_num(p->current.text);
        advance(p);
        advance(p);
        instr.rs1 = reg_num(p->current.text);
        advance(p);
        advance(p);
        instr.rs2 = reg_num(p->current.text);
        advance(p);
        return instr;
    }

    else if (strcmp(p->current.text, "addi") == 0) {
        instr.op = ADDI;
        advance(p);
        instr.rd = reg_num(p->current.text);
        advance(p);
        advance(p);
        instr.rs1 = reg_num(p->current.text);
        advance(p);
        advance(p);
        instr.imm = atoi(p->current.text);
        advance(p);
        return instr;
    }

    else if (strcmp(p->current.text, "lw") == 0) {
        instr.op = LW;
        advance(p);
        instr.rd = reg_num(p->current.text);
        advance(p);
        advance(p);
        instr.imm = atoi(p->current.text);
        advance(p);
        advance(p);
        instr.rs1 = reg_num(p->current.text);
        advance(p);
        advance(p);
        return instr;
    }

    else if (strcmp(p->current.text, "sw") == 0) {
        instr.op = SW;
        advance(p);
        instr.rs1 = reg_num(p->current.text);
        advance(p);
        advance(p);
        instr.imm = atoi(p->current.text);
        advance(p);
        advance(p);
        instr.rd = reg_num(p->current.text);
        advance(p);
        advance(p);
        return instr;
    }

    else if (strcmp(p->current.text, "beq") == 0) {
        instr.op = BEQ;
        advance(p);
        instr.rs1 = reg_num(p->current.text);
        advance(p);
        advance(p);
        instr.rs2 = reg_num(p->current.text);
        advance(p);
        advance(p);
        instr.imm = atoi(p->current.text);
        advance(p);
        return instr;
    }

    else if (strcmp(p->current.text, "jal") == 0) {
        instr.op = JAL;
        advance(p);
        instr.rd = reg_num(p->current.text);
        advance(p);
        advance(p);
        instr.imm = atoi(p->current.text);
        advance(p);
        return instr;
    }

    else if (strcmp(p->current.text, "ret") == 0) {
        instr.op = RET;
        return instr;
    }

    return instr;
}
