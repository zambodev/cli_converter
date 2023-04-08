# Compiler serttings
CC = cc
CFLAGS = -Wall -g
LFLAGS = -lm

# Folders
SRC = src
BUILD = build
BIN = bin

# Files
C_FILES = $(wildcard $(SRC)/*.c)
O_FILES = $(C_FILES:.c=.o)
B_FILES = $(addprefix $(BUILD)/, $(notdir $(O_FILES)))
EXE = $(BIN)/conv
INS_EXE = /bin/conv

# Compile
all: create_dir $(O_FILES) $(EXE)

# Compile buffer
%.o : %.c 
	@echo -n 'Compiling: $^ -> $@ -- '
	@ $(CC) -c $^ -o $(BUILD)/$(notdir $@) $(CFLAGS)
	@echo done

$(EXE) : $(B_FILES)
	@echo -n 'Linking: $(O_FILES) $^ -> $@ -- '
	@ $(CC) $^ -o $@ $(CFLAGS) $(LFLAGS)
	@echo done

# Create directories
create_dir:
ifeq ("$(wildcard $(BIN))", "")
	@echo -n 'Creating $(BIN) folder -- '
	@ mkdir $(BIN)
	@echo done
endif
ifeq ("$(wildcard $(BUILD))", "")
	@echo -n 'Creating $(BUILD) folder -- '
	@ mkdir $(BUILD)
	@echo done
endif


# Clear folders
clean:
	rm $(BIN)/* $(BUILD)/*

# Delete also the directory
cleanall:
ifneq ("$(wildcard $(BIN))", "")
	@echo -n 'Cleaning $(BIN) -- '
	@ rm -r $(BIN)/
	@echo done
endif
ifneq ("$(wildcard $(BUILD))", "")
	@echo -n 'Cleaning $(BUILD) -- '
	@ rm -r $(BUILD)/
	@echo done
endif
ifneq ("$(wildcard *.txt)", "")
	@echo -n 'Removing *.txt -- '
	@ rm *.txt
	@echo done
endif	
	

test:
	@ clear
	@ make cleanall
	@ make

install: 
	make
	mv $(EXE) $(INS_EXE)	

