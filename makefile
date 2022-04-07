library:main.o bookmanagement.o  user.o do_book.o option.o
	gcc -std=c99 -Wall -o $@ $^
.c.o:
	gcc -std=c99 -Wall -c $<
clean:
	rm -rf *.o library