build:
	make object
	$(CC) $(CFLAGS) main.c libtree.a -o tree

objectlist:
	$(MAKE) -C ../doublylinkedlist object
	mv ../doublylinkedlist/libdoublylinkedlist.o .
objectstack:
	$(MAKE) -C ../stack object
	mv ../stack/libstack.o .
object:
	make objectstack
	make objectlist
	$(CC) $(CFLAGS) -c tree.c -Wall -Wextra -o libtree.o  
	ar ruv libtree.a libtree.o libstack.o libdoublylinkedlist.o

clean:
	-rm *.a
	-rm *.o

run: 
	make build
	./tree
	
valgrind:
	make build
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./tree
