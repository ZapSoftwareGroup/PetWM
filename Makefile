CC = gcc
CFLAGS = -Wall
LDFLAGS = -lX11

SRCFILES = $(wildcard ./*.c)
OBJFILES = $(SRCFILES:c=o)

all: petwm clean

petwm: $(OBJFILES)
	$(CC) -o petwm $^ $(CFLAGS) $(LDFLAGS)

.c.o:
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	find . -name "*.o" | xargs rm -f

distclean: clean
	rm -f petwm

.PHONY: all clean distclean petwm
