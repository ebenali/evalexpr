# Recursive descent arithmetical expression evaluator
Currently works for arbitrarily parenthesized expressions with integers terms.
Will not hande leading ```+/-``` before first parens, or avoidance of division by zero, due to limitations of original code style guidelines. Most comments also had to be stripped out before code submission and may be a code exercise to recreate a few weeks from now...

Real/floating point terms should also be trivial to add.

# Source code Breakdown
Compiles with clang/gcc in reasonably modern UNIX-like environments.

## libc
File names of the form ```libc_*.{c,h}```
Implementation of certain standard C library interfaces as well as some non-standard ones written in terms of [malloc(3)](http://pubs.opengroup.org/onlinepubs/9699919799/functions/malloc.html) and [free(3)](http://pubs.opengroup.org/onlinepubs/9699919799/functions/free.html) system standard library calls, and the [write(2)](http://pubs.opengroup.org/onlinepubs/9699919799/functions/write.html) syscall.

## Tokenizer
Files ```tokctx_*.{c,h}```, ```toklist_*.{c,h}```, ```token_*.{c,h}``` are generic and mostly reusable.
Files ```lexer*.c``` contain the hardcoded rules for extracting arithmetic tokens.

## Evaluator
See ``main.c`` for recursive evaluator and supporting code.
