![GitHub](https://img.shields.io/github/license/Zambo-dev/cli_converter)

# Number converter

Command line interface number converter with many functionalities and cool features

<br />

## How to install

```shell
# Compile the code and move the executable into ./bin
make

# Clear all folders, compile the code and move the executable into ./bin
make test

# Compile the code and move the executable into /bin
make install


```

<br />

## How to use
```shell
conv <number> <base> <new_base>
```

Options:
```shell
-h --help						Show help page
-l <n> --last <n>				Print last-n conversion
-r <n> --redo <n>				Remake last conversion with new <n> base
```

<br />

**NOTE**: The conversion history file, conv_history.bin, is stored into /tmp 
