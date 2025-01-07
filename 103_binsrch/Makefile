CXX = g++
CXXFLAGS = -g -std=gnu++98 -Wall -Werror -pedantic
all: test-bsearch
test-bsearch: test-bsearch.o search.o function.o
	$(CXX) $(CXXFLAGS) -o test-bsearch test-bsearch.o search.o function.o
test-bsearch.o: test-bsearch.cpp function.h
	$(CXX) $(CXXFLAGS) -c test-bsearch.cpp
search.o: search.cpp function.h
	$(CXX) $(CXXFLAGS) -c search.cpp
function.o: function.cpp function.h
	$(CXX) $(CXXFLAGS) -c function.cpp
clean:
	rm -f *.o test-bsearch
