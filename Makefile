IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -lgtest -lpthread

LIBS=-lm
ODIR = .
_DEPS = graph-lib.h graph-node.h common.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = graph-lib-test.o graph-lib.o common.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

graph-lib-test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 