CC=clang
CFLAGS= -Wall -Wextra -Werror -Wstrict-prototypes -pedantic
LFLAGS= -lm

EXEC=colorb
OBJS=\
	colorb.o \
	io.o \
	bmp.o \

TEST_OBJS=\
	iotest.o \
	io.o\

all: colorb iotest

colorb: $(OBJS)
	$(CC) $(LFLAGS) -o colorb $(OBJS)

iotest: $(TEST_OBJS)
	$(CC) $(LFLAGS) -o iotest $(TEST_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f colorb iotest $(OBJS) $(TEST_OBJS)

format:
	clang-format -i -style=file *.[ch]

scan-build: clean
	scan-build --use-cc=$(CC) make