![GitHub](https://img.shields.io/github/license/Zambo-dev/cli_converter)

# Number converter

Command line interface number converter with many functionalities and cool features

<br />

## How to install

```shell
# Compile the code and move the executable into ./bin
make

# Clear all folders, ompile the code and move the executable into ./bin
make test

# Compile the code and move the executable into /bin
make install


```

<br />

## Help page
```shell
Default:                        <number> <base> <new_base>
-h --help:                      Show this help page
-l <n> --last <n>:              Print last-n conversion
-r <n> --redo <n>:              Remake last conversion with new <n> base
```
<br />

**NOTE**: The conversion history file, conv_history.bin, is stored into /tmp 
