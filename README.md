# Recursive descent arithmetical expression evaluator
Currently works for arbitrarily parenthesized expressions with integers terms.
Will not hande leading +/- before first parens, or avoidance of division by zero, due to original code style guidelines.
Real/floating point terms should also be trivial to add.

# Source code Breakdown
Compiles with clang/gcc in reasonably modern UNIX-like environments.

## libc
File names of the form ```libc_*.{c,h}```
Implementation of certain standard C library interfaces as well as some non-standard ones written in terms of malloc(3), free(3) and write(2) syscalls.

## Tokenizer
Files ```tokctx_*.{c,h}```, ```toklist_*.{c,h}```, ```token_*.{c,h}``` are generic and mostly reusable.
Files ```lexer*.c``` contain the hardcoded rules for extracting arithmetic tokens.

## Evaluator
See ``main.c`` for recursive evaluator and supporting code.
