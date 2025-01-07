CXX = g++
CXXFLAGS = -std=gnu++98 -Wall -Werror -pedantic

TARGET = test-bstmap
SRC = test-bstmap.cpp
OBJ = $(SRC:.cpp=.o)

HEADERS = bstmap.h map.h

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)
