CC=clang
CFLAGS=-c -Wall
LDFLAGS=
SOURCES= hash.c student.c heap.c binTree.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=final_project

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) main.c -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o
	rm -rf $(EXECUTABLE)

lint:
	clang-format *.c *.h
