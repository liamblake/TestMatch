
IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=../build
SDIR = ../src

LIBS=-lm

_DEPS = Cards.h Player.h Simulation.h Utility.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = demonstrative_test.o Cards.o Player.o Simulation.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(pathsubst %,$(SDIR)/%.c) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test_inns: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 