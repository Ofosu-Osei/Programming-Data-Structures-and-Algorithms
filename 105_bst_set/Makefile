CXX = g++
CXXFLAGS = -std=gnu++98 -Wall -Werror -pedantic

TARGET = test-bstset
SRC = test-bstset.cpp
OBJ = $(SRC:.cpp=.o)

HEADERS = bstset.h set.h

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)
