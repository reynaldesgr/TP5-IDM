CC = g++                      
CFLAGS =  -I ../../Random/include -fopenmp  
LDFLAGS = -L ../../Random/lib -lCLHEP-Random-2.1.0.0 -static 

# Directory to store object files
OBJ_DIR = obj

# Create the necessary object directories
$(shell mkdir -p $(OBJ_DIR) $(OBJ_DIR)/Random/include)

# Source file and target executable
SRC = main.c
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
TARGET = main

# Default target to build the executable
all: $(TARGET)

# Rule to link object files and produce the final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)

# Rule to compile .c files into .o files in the obj/ directory
$(OBJ_DIR)/%.o: %.c
	$(shell mkdir -p $(dir $@)) 
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rule to clean compiled files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Rule to force recompilation of everything
rebuild: clean all

# Phony targets to avoid file conflicts
.PHONY: all clean rebuild