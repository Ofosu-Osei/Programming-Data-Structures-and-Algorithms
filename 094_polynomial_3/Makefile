CCFLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3
polyTest:  test3.o
	g++ -o polyTest $(CCFLAGS) test3.o

%.o: %.cpp poly.hpp
	g++ -c $(CCFLAGS) $<

clean:
	rm -f *.o  *~ polyTest
