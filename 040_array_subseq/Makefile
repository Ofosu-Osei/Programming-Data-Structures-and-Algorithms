# Define the compiler
CC = gcc

# Define any compile-time flags
CFLAGS = -std=gnu99  -Wall -Werror

# Define the target executable name
TARGET = maxSeq

# List all the object files 
OBJ = maxSeq.o test-subseq.o 

# Rule for making the final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Rule for making the object files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Rule for cleaning up generated files
clean:
	rm -f $(TARGET) $(OBJ)
