#include <stdio.h>
#include <string.h>
#include "../include/elf_writer.h"

void elf_write_instr(ELFWriter* e, uint32_t instr) {
    e->code[e->count++] = instr;
}

void elf_emit(ELFWriter* e, const char* filename) {
    FILE* f = fopen(filename, "wb");

    const char shstrtab[] = "\0.text\0.shstrtab\0";
    int shstrtab_size = sizeof(shstrtab);
    int code_size     = e->count * 4; 

    int code_offset     = 64;        
    int shstrtab_offset = code_offset + code_size;
    int shdr_offset     = shstrtab_offset + shstrtab_size;
    shdr_offset = (shdr_offset + 7) & ~7;

    uint8_t ehdr[64];
    memset(ehdr, 0, 64);
    ehdr[0]=0x7f; ehdr[1]='E'; ehdr[2]='L'; ehdr[3]='F';
    ehdr[4]=2;   
    ehdr[5]=1;
    ehdr[6]=1;
    ehdr[7]=0;
    *(uint16_t*)(ehdr+16) = 1;
    *(uint16_t*)(ehdr+18) = 0xF3;
    *(uint32_t*)(ehdr+20) = 1;
    *(uint64_t*)(ehdr+40) = shdr_offset;
    *(uint32_t*)(ehdr+48) = 0x4;
    *(uint16_t*)(ehdr+52) = 64;
    *(uint16_t*)(ehdr+58) = 64;
    *(uint16_t*)(ehdr+60) = 3;
    *(uint16_t*)(ehdr+62) = 2;

    fwrite(ehdr, 64, 1, f);
    fwrite(e->code, code_size, 1, f);
    fwrite(shstrtab, shstrtab_size, 1, f);

    int cur = 64 + code_size + shstrtab_size;
    while (cur < shdr_offset) { fputc(0, f); cur++; }

    uint8_t shdr[64];

    memset(shdr, 0, 64);
    fwrite(shdr, 64, 1, f);

    memset(shdr, 0, 64);
    *(uint32_t*)(shdr+0)  = 1; 
    *(uint32_t*)(shdr+4)  = 1;
    *(uint64_t*)(shdr+8)  = 6;
    *(uint64_t*)(shdr+24) = code_offset; 
    *(uint64_t*)(shdr+32) = code_size; 
    *(uint32_t*)(shdr+56) = 4;       
    fwrite(shdr, 64, 1, f);

    memset(shdr, 0, 64);
    *(uint32_t*)(shdr+0)  = 7; 
    *(uint32_t*)(shdr+4)  = 3; 
    *(uint64_t*)(shdr+24) = shstrtab_offset;
    *(uint64_t*)(shdr+32) = shstrtab_size;  
    *(uint32_t*)(shdr+56) = 1;            
    fwrite(shdr, 64, 1, f);

    fclose(f);
}
