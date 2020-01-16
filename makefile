CC = gcc
AR = ar -rcs
OBJECTS_MAIN = trie.o
FLAGS = -I. -Wall

all: frequency

frecuency: $(OBJECTS_MAIN)
	$(CC) $(FLAGS) -o frequency $(OBJECTS_MAIN)

trie.o: trie.c
	$(CC) $(FLAGS) -c trie.c

.PHONY: clean all

clean:
	rm -f *.o frequency