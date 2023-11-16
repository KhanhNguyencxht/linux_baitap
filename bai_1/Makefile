.PHONY: ALL clean

NAME_SHARED := KH_SHARED
NAME_STATIC := KH_SHARED

CURRENT_DIR := .
BIN_DIR  := $(CURRENT_DIR)/bin
INC_DIR  := $(CURRENT_DIR)/inc

LIB_DIR  := $(CURRENT_DIR)/lib
LIB_SHARED := $(LIB_DIR)/shared
LIB_STATIC := $(LIB_DIR)/static

OBIS_DIR := $(CURRENT_DIR)/objs
SRC_DIR  := $(CURRENT_DIR)/src

INC_FLAGS := -I $(INC_DIR)

NAME := HELLO_1

CC := gcc

mk_objs_static:
	$(CC) -c $(CURRENT_DIR)/main.c -o $(OBIS_DIR)/main.o $(INC_FLAGS)
	$(CC) -c $(SRC_DIR)/hello.c -o $(OBIS_DIR)/hello.o $(INC_FLAGS)
	$(CC) -c $(SRC_DIR)/matht.c -o $(OBIS_DIR)/matht.o $(INC_FLAGS)

mk_static:
	ar rcs $(LIB_STATIC)/lib$(NAME_STATIC).a $(OBIS_DIR)/matht.o  $(OBIS_DIR)/hello.o

all_static:

	$(CC) $(OBIS_DIR)/main.o -L$(LIB_STATIC) -l$(NAME_STATIC) -o $(BIN_DIR)/use-static-linked


mk_objs_shared:
	$(CC) -c $(CURRENT_DIR)/main.c -o $(OBIS_DIR)/main.o $(INC_FLAGS)
	$(CC) -c -fPIC $(SRC_DIR)/hello.c -o $(OBIS_DIR)/hello.o $(INC_FLAGS)
	$(CC) -c -fPIC $(SRC_DIR)/matht.c -o $(OBIS_DIR)/matht.o $(INC_FLAGS)

mk_shared:
	$(CC) -shared $(OBIS_DIR)/hello.o $(OBIS_DIR)/matht.o -o $(LIB_SHARED)/lib$(NAME_SHARED).so

all_shared:
	$(CC) $(OBIS_DIR)/main.o -L$(LIB_SHARED) -l$(NAME_SHARED) -o $(BIN_DIR)/use-shared-library

clean:
	rm -rf $(OBIS_DIR)/*
	rm -rf $(LIB_SHARED)/*
	rm -rf $(LIB_STATIC)/*
	rm -rf $(BIN_DIR)/*
