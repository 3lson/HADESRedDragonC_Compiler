# HADESRedDragonC_Compiler

**Please Note:** Full implementation is available on the **restructure** branch

The source language is pre-processed C90, and the target language is RISC-V assembly. The target environment is Ubuntu 22.04

## Getting Started

### Dependencies
The dependencies are listed in the [Dockerfile](https://github.com/3lson/HADESRedDragonC_Compiler/blob/main/Dockerfile)

### Usage
To make the compiler, run the following command:
```bash
make
```
To run the compiler, run the followign commmand, replacing the flags:
- `-S` for the input file path
- `-o` for the output file path

So to compile an example program we can:
```bash
bin/c_compiler -S "./compiler_tests/_example/example.c" -o "./example.s"
```
## Credits 
- [Elson Tho]
- [Ahmed Hamid]
