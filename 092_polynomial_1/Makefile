CCFLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3
polynomialTest:  test1.o
	g++ -o polynomialTest $(CCFLAGS) test1.o

%.o: %.cpp poly.hpp
	g++ -c $(CCFLAGS) $<

clean:
	rm -f *.o  *~ polynomialTest
