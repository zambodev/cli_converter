**NOTE**: This is the main branch, written in C, there is a "rust" branch that is **fully working**, and a just for fun "asm" branch that is only partially build<br>
This became my go to project while learning new languages, so new branches will be created in the future

# cli_converter

Command line interface number converter with many functionalities and cool features

<br />

## How to install

```shell
# Compile the code
make

# Clear all folders, compile the code and move the executable into ./bin
make test

# Compile the code and move the executable into /bin
sudo make install


```

<br />

## How to use
```shell
conv <number> <base> <new_base>
```

Options:
```shell
-h --help                       Show help page
-l <n> --last <n>               Print last-n conversion
-r <n> --redo <n>               Remake last conversion with new <n> base
```

<br />

**NOTE**: The conversion history file, conv_history.bin, is stored into /tmp 
