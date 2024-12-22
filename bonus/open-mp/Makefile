EXEC = MTNeutron

SRC = MTNeutron.cpp

CC = gcc
CFLAGS = -O2 -Wall -fopenmp 

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC) -lm

clean:
	rm -f $(EXEC)

run: $(EXEC)
	./$(EXEC)