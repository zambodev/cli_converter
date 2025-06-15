# cli-converter
Simple and easy to use commanbd line number converter

NOTE: The original project was written in C, and due to learning purposes it's been rewritten in Rust

## How to install
```bash
# Coming soon...
```

## Help 
```bash
Usage: 
      conv [OPTIONS] [PREFIX]number 
      conv [OPTIONS] [PREFIX]number [BASE] 

Prefixes: 
      0x              16 base number
                      10 base number (no prefix needed)
      0               8 base number
      0b              2 base number

Bases: 
      16              to 16 base
      10              to 10 base
      8               to 8 base
      2               to 2 base

Options: 
      -h, --help      Display this message
```

## Examples
```bash
$ conv 0x1234
hex: 1234
dec: 4660
oct: 11064
bin: 1001000110100
```

```bash
$ conv 0x1234
bin: 1001000110100
```