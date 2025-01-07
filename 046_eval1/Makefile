CFLAGS=-Wall -Werror --std=gnu99 -pedantic -ggdb3
PROVIDED_OBJS=dummy-s2.o dummy-s3.o provided.o
RMOBJS=$(filter-out $(PROVIDED_OBJS), $(wildcard *.o))

all: launches-step1  launches-step2 launches-step3 launches-step4
	@echo "Made all launches targets"
launches-step1: step1.o myinput.o  provided.o dummy-s2.o dummy-s3.o
	gcc -o $@ $(CFLAGS) $^ -lm

launches-step2: step2.o myinput.o  provided.o planet_util.o dummy-s3.o
	gcc -o $@ $(CFLAGS) $^ -lm

launches-step3: step3.o myinput.o  provided.o planet_util.o  target.o
	gcc -o $@ $(CFLAGS) $^ -lm

launches-step4: step4.o myinput.o  provided.o planet_util.o  target.o iter_target.o
	gcc -o $@ $(CFLAGS) $^ -lm

launches-step4-debug: step4.o myinput.o  provided.o planet_util.o  target.o iter_target-debug.o
	gcc -o $@ $(CFLAGS) $^ -lm

iter_target-debug.o: iter_target.c *.h
	gcc -o $@ -DDEBUG_OUT -c $(CFLAGS) $<

%.o: %.c *.h
	gcc -c $(CFLAGS) $<

.PHONY: provided-objs

provided-objs: $(PROVIDED_OBJS)
	@echo "Made object files to provide to students"
clean:
	rm -f $(RMOBJS) *~ launches-step? launches-step4-debug
.PHONY: provided-outputs
provided-outputs: launches-step1 launches-step2 launches-step3 launches-step4 launches-step4-debug
	./launches-step1 sol.txt > sol-step1-output.txt
	./launches-step2 sol.txt > sol-step2-output.txt 
	./launches-step3 sol.txt launches1.txt > sol-step3-output.txt
	./launches-step4 sol.txt launches1.txt > sol-step4-output.txt
	./launches-step4 simple.txt launches_simple.txt  > simple-step4.txt
	./launches-step4-debug simple.txt launches_simple.txt  > simple-step4-debug.txt
