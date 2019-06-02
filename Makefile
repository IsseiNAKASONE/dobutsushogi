CC = gcc

fuji: main.o io.o shogi.o move.o capture.o judge.o tree.o evaluate.o attack.o
	CC -o fuji main.o io.o shogi.o move.o capture.o judge.o tree.o evaluate.o attack.o
main.o:		main.c
	CC -c main.c
io.o:		io.c
	CC -c io.c
shogi.o:	shogi.c
	CC -c shogi.c
move.o:		move.c
	CC -c move.c
capture.o:	capture.c
	CC -c capture.c
judge.o:	judge.c
	CC -c judge.c
tree.o:		tree.c
	CC -c tree.c
evaluate.o:	evaluate.c
	CC -c evaluate.c
attack.o:	attack.c
	CC -c attack.c

.PHONY: clean
clean:
	rm -f *.o *.h~ *.c~
