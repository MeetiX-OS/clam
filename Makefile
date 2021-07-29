PROJNAME = clam

CC = gcc
STD = c90
CFLAGS = -std=$(STD) -Wall -Wpedantic -Wextra -Wno-endif-labels -g

SRC = src
OBJ = obj
TRG = target
SOURCES = $(wildcard $(SRC)/*.c)
OBJECTS = $(SOURCES:$(SRC)/%.c=$(OBJ)/%.o)
OUTPUT = $(TRG)/$(PROJNAME)

run:
	@ echo Running $(OUTPUT)
	./$(OUTPUT)

build: $(OBJECTS)
	- mkdir -p $(TRG)
	$(CC) -o $(OUTPUT) $^

clean:
	- rm -Vrf $(OBJ)
	- rm -Vrf $(TRG)

$(OBJ)/%.o: $(SRC)/%.c
	- mkdir -p $(OBJ)
	$(CC) -c $(CFLAGS) -o $@ $<