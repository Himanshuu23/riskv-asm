#ifndef ELF_WRITER_H
#define ELF_WRITER_H 

#include <stdint.h>

typedef struct 
{
    uint32_t code[1024];
    int      count;
} ELFWriter;

void elf_write_instr(ELFWriter* e, uint32_t instr);
void elf_emit(ELFWriter* e, const char* filename);

#endif
