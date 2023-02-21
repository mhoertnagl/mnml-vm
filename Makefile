TARGET = mnml

SRC_DIR = ./src
OUT_DIR = ./build

CC = clang
CFLAGS = -std=c17 -g -Wall

LIBS += -lSDL2

DEPS += -I/usr/include/SDL2 
DEPS += -I$(SRC_DIR)

INC = $(shell find $(SRC_DIR) -name '*.h')
SRC = $(shell find $(SRC_DIR) -name '*.c')
OBJ = $(patsubst %.c, %.o, $(SRC))

all: $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) $(DEPS) $^ -o $(OUT_DIR)/$@

%.o: %.c $(INC)
	$(CC) -c $(CFLAGS) $(LIBS) $(DEPS) $< -o $@

.PHONY: clean

clean:
	find . -type f -name '*.o' -delete
	rm -f $(OUT_DIR)/$(TARGET)
