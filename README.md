# Whitespace Stripper

Whitespace Stripper (aka `whtstrp`) is a simple utility to strip a file of white-space characters.
This program will also preserve white-space within quoted strings (single and double) as well.

## How to use

To use the program, do the following:

```bash
whtstrp [OPTIONS] [FILE]
```

which will send its output to `stdout`.

To save output to a file, use the redirection operator `>`:

```bash
whtstrp [OPTIONS] [FILE] > OUPUT_FILE
```

### Arguments

By default, `whtstrp` will remove all possible white-space characters from a file.
You can, however, customize what white-space characters you want to remove by specifying the following arguments.

- `-n` strip newline characters.
- `-r` strip carriage returns.
- `-s` strip spaces.
- `-t` strip tabs.
- `-x` strip white-space characters for XML like formats (all other flags ignored).
- `--help` display help information.
- `--version` output version and copyright information, then exits.

## Building

To build `whtstrp`, simply run `make`.

Note that the `makefile` assumes you're using `gcc` as your C compiler.
If you're using a different compiler, go into the `makefile` and change the `CC` variable to your specific compiler.

## Contributing

If you find any issues, or feel an enhancement can be made, create an issue on GitHub, and use an appropriate tag along with it.

For issue and bugs, please describe in detail what the issue is and steps to recreate the issue.

## Copyright and License

This software is distributed under GPLv3.
See `LICENSE` for more information.
