# Define the compiler
CC = gcc

# Define compile-time flags
CFLAGS = -Wall -Werror -g

# Define the target executable name
TARGET = my-power

# List all the object files 
OBJ = power.o test-power.o 

# Rule for making the final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Rule for making the object files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Rule for cleaning up generated files
clean:
	rm -f $(TARGET) $(OBJ)
