chess: main.o square.o board.o piece.o moves.o list.o game.o tree.o 
	$(CC) main.o square.o board.o piece.o moves.o list.o game.o tree.o -o chess -L . -lpthread

main.o: main.c main.h
	$(CC) -c -Wall -pedantic -Werror main.c -o main.o

square.o: square.c square.h
	$(CC) -c -Wall -pedantic -Werror square.c -o square.o

board.o: board.c board.h
	$(CC) -c -Wall -pedantic -Werror board.c -o board.o

piece.o: piece.c piece.h
	$(CC) -c -Wall -pedantic -Werror piece.c -o piece.o

moves.o: moves.c moves.h
	$(CC) -c -Wall -pedantic -Werror moves.c -o moves.o

list.o: list.c list.h
	$(CC) -c -Wall -pedantic -Werror list.c -o list.o

game.o: game.c game.h
	$(CC) -c -Wall -pedantic -Werror game.c -o game.o


tree.o: tree.c tree.h
	$(CC) -c -Wall -pedantic -Werror tree.c -o tree.o

lpthread.o: lpthread.c lpthread.h
	gcc -O -c lpthread.c



clean:
	rm -f chess *.o *.a *.gch












