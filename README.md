# riscv-asm

A RISC-V assembler written in C99 from scratch. Takes `.asm` source files and outputs ELF `.o` binaries. Zero dependencies.

## What It Does

Takes RISC-V assembly source code and compiles it to a 64-bit ELF object file a RISC-V CPU can run.
```
Source (.asm)
     ↓
Lexer → Tokens
     ↓
Parser → Instruction structs
     ↓
Encoder → 32-bit machine code
     ↓
ELF Writer → .o binary
```

## Building
```bash
gcc src/main.c src/lexer.c src/parser.c src/encoder.c src/elf_writer.c -Iinclude -o asm
```

No cmake. No dependencies. Just gcc.

## Usage
```bash
./asm input.asm output.o
riscv64-linux-gnu-objdump -d output.o
```

## Supported Instructions

`add`, `sub`, `addi`, `lw`, `sw`, `beq`, `jal`, `ret`

## Architecture

| File | What It Does |
|------|-------------|
| `lexer.c` | Tokenises assembly source |
| `parser.c` | Parses tokens into instruction structs |
| `encoder.c` | Encodes instructions to 32-bit machine code |
| `elf_writer.c` | Emits ELF64 object file |

## License

MIT
