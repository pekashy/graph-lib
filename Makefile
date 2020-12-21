IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -lgtest -lpthread

LIBS=-lm
ODIR = .
_DEPS = lib/graph-lib.h lib/graph-node.h objects/common.h utils/graph-iterator.h utils/visitors.h utils/dispatcher.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = graph-lib-test.o lib/graph-lib.o objects/common.o utils/graph-iterator.o utils/visitors.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

graph-lib-test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(ODIR)/lib/*.o $(ODIR)/objects/*.o $(ODIR)/utils/*.o *~ core $(INCDIR)/*~ 