ttt -- Command-line Tic Tac Toe
-------------------------------

Copyright (c) 2015 Andrew A. Cashner

This is a Tic Tac Toe program designed for the command line or TTY terminal.

## Compiling

The program written in `CWEB`. 
To compile it you will need the `CWEB` utilites, which are most easily obtained
as part of the TeXLive distribution from the TeX Users' Group at
<http://www.tug.org>.

The actual program is `ttt.w`.
In a terminal, run `ctangle ttt`, which will produce `ttt.c`.
Compile this C program with your preferred compiler, e.g., `gcc -o ttt ttt.c`.

To produce a PDF of the complete program with its documentation, run `cweave
ttt`, which will produce `ttt.tex`.
Compile this Plain TeX document with, `pdftex ttt`.

### TL;DR

 - Copy `ttt.w` to your computer.
 - Install TeXLive.
 - Run these commands:
     + `ctangle ttt && gcc -o ttt ttt.c`
	 + `cweave ttt && pdftex ttt`

