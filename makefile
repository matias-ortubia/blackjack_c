CC = gcc
LDFLAGS = -lm
OBJ_DIR = obj
BIN_DIR = bin
SRC_DIR = src
INC_DIR = inc
CFLAGS = -std=c99 -Wall -I$(INC_DIR) -Werror -pedantic -g

OBJECTS = $(OBJ_DIR)/main.o\
	  $(OBJ_DIR)/card.o\
	  $(OBJ_DIR)/deck.o\

TARGET = $(BIN_DIR)/blackjack.exe

all: $(TARGET)

$(TARGET): $(OBJECTS)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $(TARGET) 

$(OBJ_DIR)/card.o: $(SRC_DIR)/card.c $(INC_DIR)/card.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/card.c -o $@

$(OBJ_DIR)/deck.o: $(SRC_DIR)/deck.c $(INC_DIR)/deck.h $(INC_DIR)/card.h
	mkdir -p $(OBK_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/deck.c -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(INC_DIR)/card.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $@

.PHONY: clean
clean:
	rm -r $(OBJ_DIR) $(BIN_DIR)
