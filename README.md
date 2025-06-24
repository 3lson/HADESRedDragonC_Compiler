# HADESRedDragonC_Compiler

<p align="left">
  <a href="https://en.wikipedia.org/wiki/C90_(C_standard_revision)">
    <img src="https://img.shields.io/badge/Language-C90-blue.svg" alt="C90 Standard">
  </a>
  <a href="https://riscv.org/">
    <img src="https://img.shields.io/badge/Target-RISC--V-green.svg" alt="RISC-V ISA">
  </a>
  <a href="https://ubuntu.com/">
    <img src="https://img.shields.io/badge/Platform-Ubuntu%2022.04-E95420.svg" alt="Ubuntu">
  </a>
  <a href="https://www.gnu.org/software/make/">
    <img src="https://img.shields.io/badge/Build%20System-Make-lightgrey.svg" alt="Make Build System">
  </a>
  <a href="https://www.docker.com/">
    <img src="https://img.shields.io/badge/Environment-Docker-2496ED.svg" alt="Docker">
  </a>
</p>


HADESRedDragonC_Compiler is a **C90-to-RISC-V compiler** developed as part of the Instruction Architecture and Compilers coursework at Imperial College London. It compiles pre-processed C90 source code into RISC-V assembly targeting Ubuntu 22.04, focusing on correctness, portability, and alignment with the RISC-V calling conventions and ABI. 

The final submitted compiler can be found on the **restructure** branch.

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
