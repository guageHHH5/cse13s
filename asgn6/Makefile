CC=clang
CFLAGS= -Wall -Wextra -Werror -Wstrict-prototypes -pedantic -gdwarf-2
VFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose


OBJSS=node.o pq.o bitwriter.o 
OBJS=huff.o $(OBJSS)
OBJS2=pqtest.o $(OBJSS)
OBJS3=nodetest.o $(OBJSS)
OBJS4=bwtest.o $(OBJSS)
LIBS1=io-$(shell uname -m).a

all: huff pqtest nodetest bwtest

huff: $(OBJS) $(LIBS1)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS1)

pqtest: $(OBJS2) $(LIBS1)
	$(CC) $(CFLAGS) -o $@ $(OBJS2) $(LIBS1)

nodetest: $(OBJS3) $(LIBS1)
	$(CC) $(CFLAGS) -o $@ $(OBJS3) $(LIBS1)

bwtest: $(OBJS4) $(LIBS1)
	$(CC) $(CFLAGS) -o $@ $(OBJS4) $(LIBS1)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f huff nodetest pqtest bwtest bwtest.out *.o $(OBJS) $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(TEST_OBJS)

valgrind: clean all
	valgrind $(VFLAGS) ./huff -i input.txt -o output.txt


format:
	clang-format -i -style=file *.[ch]

scan-build: clean
	scan-build --use-cc=$(CC) make
