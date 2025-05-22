CUR_DIR = ./
BIN_DIR = $(CUR_DIR)/bin
INC_DIR = $(CUR_DIR)/inc
LIB_DIR = $(CUR_DIR)/lib
LIB_STATIC_DIR = $(LIB_DIR)/static
LIB_SHARED_DIR = $(LIB_DIR)/shared
OBJ_DIR = $(CUR_DIR)/obj
OBJ_STATIC_DIR = $(OBJ_DIR)/static
OBJ_SHARED_DIR = $(OBJ_DIR)/shared
SRC_DIR = $(CUR_DIR)/src


create_obj:
	gcc -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o -I $(INC_DIR)
	gcc -c -fPIC $(SRC_DIR)/hello.c -o $(OBJ_SHARED_DIR)/hello.o -I $(INC_DIR)
	gcc -c $(SRC_DIR)/hello.c -o $(OBJ_STATIC_DIR)/hello.o -I $(INC_DIR)

create_static_lib: 
	ar rcs $(LIB_STATIC_DIR)/libhello.a $(OBJ_STATIC_DIR)/hello.o 

create_shared_lib: 
	gcc -shared $(OBJ_SHARED_DIR)/hello.o -o $(LIB_SHARED_DIR)/libhello.so -I $(INC_DIR)

linking_static: 
	gcc $(OBJ_DIR)/main.o  -L$(LIB_STATIC_DIR) -lhello -o $(BIN_DIR)/statically-linked

linking_shared: 
	gcc $(OBJ_DIR)/main.o -L$(LIB_SHARED_DIR) -lhello -o $(BIN_DIR)/use-shared-library

all: create_obj create_shared_lib create_static_lib linking_shared linking_static
	@echo "Create Shared Library"
	@echo "Create Static Library"

clean:
	rm -rf $(OBJ_SHARED_DIR)/*.o
	rm -rf $(OBJ_STATIC_DIR)/*.o
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(LIB_SHARED_DIR)/*.so
	rm -rf $(LIB_STATIC_DIR)/*.a
	rm -rf $(BIN_DIR)/use-shared-library
	rm -rf $(BIN_DIR)/statically-linked