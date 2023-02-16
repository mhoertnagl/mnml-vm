TARGET = mnml

SRC_DIR = ./src
OUT_DIR = ./build

CC = clang
CFLAGS = -std=c17 -g -Wall

LIBS += -lSDL2

DEPS += -I/usr/include/SDL2 
DEPS += -I$(SRC_DIR)

#SRC = $(wildcard $(addsuffix /*.c, $(SRC_DIR)))
INC = $(shell find $(SRC_DIR) -name '*.h')
SRC = $(shell find $(SRC_DIR) -name '*.c')
OBJ = $(patsubst %.c, %.o, $(SRC))
# OBJ = $(patsubst $(SRC_DIR), $(OUT_DIR), $(patsubst %.c, %.o, $(SRC)))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) $(DEPS) $^ -o $(OUT_DIR)/$@

%.o: %.c $(INC)
	$(CC) -c $(CFLAGS) $(LIBS) $(DEPS) $< -o $@

.PHONY: clean

clean:
	-rm -f *.o $(TARGET)
