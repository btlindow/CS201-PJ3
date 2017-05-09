OBJS = main.o scanner.o binheap.o node.o cdll.o prim.o table.o vertex.o
OPTS = -Wall -Wextra -g -std=c99

prim: $(OBJS)
	gcc $(OPTS) $(OBJS) -o prim -lm

main.o: main.c scanner.h binheap.h node.h prim.h table.h vertex.h
	gcc $(OPTS) -c main.c

scanner.o: scanner.c scanner.h
	gcc $(OPTS) -c scanner.c

binheap.o: binheap.c binheap.h cdll.h node.h
	gcc $(OPTS) -c binheap.c

prim.o: prim.c prim.h binheap.h vertex.h table.h
	gcc $(OPTS) -c prim.c

node.o: node.c node.h cdll.h vertex.h
	gcc $(OPTS) -c node.c

cdll.o: cdll.c cdll.h node.h
	gcc $(OPTS) -c cdll.c

table.o: table.c table.h
	gcc $(OPTS) -c table.c

vertex.o: vertex.c vertex.h binheap.h
	gcc $(OPTS) -c vertex.c

clean:
	rm -f prim $(OBJS)
