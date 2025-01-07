CCFLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3
polyTest:  test2.o
	g++ -o polyTest $(CCFLAGS) test2.o

%.o: %.cpp poly.hpp
	g++ -c $(CCFLAGS) $<

clean:
	rm -f *.o  *~ polyTest
