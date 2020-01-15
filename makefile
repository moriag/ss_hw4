CC = gcc
AR = ar -rcs
OBJECTS_MAIN = trie.o
FLAGS = -I. -Wall

all: frecuency

frecuency: $(OBJECTS_MAIN)
	$(CC) $(FLAGS) -o frecuency $(OBJECTS_MAIN)

trie.o: trie.c
	$(CC) $(FLAGS) -c trie.c

.PHONY: clean all

clean:
	rm -f *.o frecuency