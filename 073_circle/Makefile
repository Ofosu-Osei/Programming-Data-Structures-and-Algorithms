# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Werror -pedantic -std=c++98

# Target executable
TARGET = circles

# Source files
SRCS = main.cpp point.cpp circle.cpp

# Object files (derived from source files)
OBJS = $(SRCS:.cpp=.o)

# Default rule to build the target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean rule to remove generated files
clean:
	rm -f $(OBJS) $(TARGET)
