CC=clang
debug:   CFLAGS=-Wall -Wextra -Wstrict-prototypes -Werror -pedantic #-g
release: CFLAGS=-Wall -Wextra -Wstrict-prototypes -Werror -pedantic
LDFLAGS=-lm

EXECBIN=tsp
OBJS=\
    graph.o \
    stack.o \
    path.o \
    tsp.o \

.PHONY: all debug release clean

all: debug

debug: $(EXECBIN)

release: $(EXECBIN)

$(EXECBIN): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXECBIN) $(OBJS)

format:
	clang-format -i --style=file *.[ch]