CC = g++                      
CFLAGS =  -I ../../Random/include -fopenmp  
LDFLAGS = -L ../../Random/lib -lCLHEP-Random-2.1.0.0 -static 

OBJ_DIR = obj

$(shell mkdir -p $(OBJ_DIR) $(OBJ_DIR)/Random/include)

SRC = main.c
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c
	$(shell mkdir -p $(dir $@)) 
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild