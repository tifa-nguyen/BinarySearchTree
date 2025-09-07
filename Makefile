CC = gcc
CFLAGS = -g -Wall -Wshadow
DEPS = node.h main.c traversals.c traversals.h buildTree.c buildTree.h
TESTS = P0_test1 P0_test2 P0_test3 P0_test4 P0_test5 P0_test6
OBJ = main.o traversals.o buildTree.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

P0: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

tar:
	tar -cvf tiffany-nguyen-P0.tar $(DEPS) $(TESTS)

clean:
	rm $(OBJ) P0 *.levelorder *.preorder *.inorder
