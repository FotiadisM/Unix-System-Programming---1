CC = gcc
CFLAGS = -g3 -Wall
LDFLAGS =

BDIR = bin
ODIR = build
IDIR = include
SDIR = src

EXECUTABLE = diseaseMonitor

_DEPS = diseaseMonitor.h Date.h Patient.h HashTable.h List.h AVL.h fnclib.h maxHeap.h Queue.h defines.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o diseaseMonitor.o Date.o Patient.o HashTable.o List.o AVL.o fnclib.o maxHeap.o Queue.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

$(BDIR)/$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: clean run valgrind

run:
	./$(BDIR)/$(EXECUTABLE) -p tatas.txt -h1 4 -h2 5 -b 24

valgrind:
	valgrind --leak-check=full ./$(BDIR)/$(EXECUTABLE) -p small.txt -h1 4 -h2 5 -b 24

clean:
	rm -f $(ODIR)/*.o
	rm -f $(BDIR)/$(EXECUTABLE)