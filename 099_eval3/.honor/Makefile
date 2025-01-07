SPECIFIC_OBJS=step1.o step2.o step3.o step4.o
COMMON_OBJ=$(filter-out $(SPECIFIC_OBJS), $(patsubst %.cpp,%.o,$(wildcard *.cpp)))
BINARIES=ships-step1 ships-step2 ships-step3 ships-step4
CXXFLAGS=-Wall -Werror -ggdb3 -pedantic --std=gnu++03
all: $(BINARIES)
	@echo "made all"
ships-step%: step%.cpp $(COMMON_OBJ) *.hpp
	g++ -o $@ $(CXXFLAGS) $< $(COMMON_OBJ)
%.o: %.cpp *.hpp
	g++ -c $(CXXFLAGS) $<

clean:
	rm -rf *.o *~ $(BINARIES)

