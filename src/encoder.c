#include <stdint.h>
#include "../include/encoder.h"

uint32_t encode_r(uint32_t funct7, uint32_t rs2, uint32_t rs1, uint32_t funct3, uint32_t rd, uint32_t opcode) {
    return (funct7 << 25) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) | (rd << 7) | opcode;
}

uint32_t encode_i(uint32_t imm, uint32_t rs1, uint32_t funct3, uint32_t rd, uint32_t opcode) {
    return ((imm & 0xFFF) << 20) | (rs1 << 15) | (funct3 << 12) | (rd << 7) | opcode;
}

uint32_t encode_s(uint32_t imm, uint32_t rs2, uint32_t rs1, uint32_t funct3, uint32_t opcode) {
    return ((imm >> 5) << 25) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) | ((imm & 0x1F) << 7) | opcode;
}

uint32_t encode_b(uint32_t imm, uint32_t rs2, uint32_t rs1, uint32_t funct3, uint32_t opcode) {
    return (((imm >> 12) & 1) << 31) | (((imm >> 5) & 0x3F) << 25) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) | (((imm >> 1) & 0xF) << 8) | (((imm >> 11) & 1) << 7) | opcode;
}

uint32_t encode_j(uint32_t imm, uint32_t rd, uint32_t opcode) {
    return (((imm >> 20) & 1) << 31) | (((imm >> 1) & 0x3FF) << 21) | (((imm >> 11) & 1) << 20) | (((imm >> 12) & 0xFF) << 12) | (rd << 7) | opcode;
}

uint32_t encode(Instr instr) {
    switch(instr.op) {
        case ADD:
            return encode_r(0x00, instr.rs2, instr.rs1, 0x0, instr.rd, 0x33);
        case SUB:
            return encode_r(0x20, instr.rs2, instr.rs1, 0x0, instr.rd, 0x33);
        case ADDI: 
            return encode_i(instr.imm, instr.rs1, 0x0, instr.rd, 0x13);
        case LW:
            return encode_i(instr.imm, instr.rs1, 0x2, instr.rd, 0x03);
        case SW:
            return encode_s(instr.imm, instr.rs1, instr.rd, 0x2, 0x23);
        case BEQ:
            return encode_b(instr.imm, instr.rs2, instr.rs1, 0x0, 0x63);
        case JAL:
            return encode_j(instr.imm, instr.rd, 0x6F);
        case RET:
            return encode_i(0, 1, 0x0, 0, 0x67);
    }
}
