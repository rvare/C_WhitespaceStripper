# C Whitespace Stripper Utility

This C program is a simple utility to strip a file of all possible whitespace characters.
This program can also preserve whitespace within quoted strings as well.

# How to use

To use the program after compiling, do the following:

```bash
./whtstrp.out <dir to file>
```

It will output to `stdout`. To save output to a file, use the redirection operator `>`:

```bash
./whtstrp.out <dir to file> > <dir to new file>
```
