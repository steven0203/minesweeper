game: main.o game.o sect_play.o menu.o gametime.o mine.o 
	g++ -o game main.o game.o sect_play.o menu.o gametime.o mine.o -lncurses
main.o : main.cpp game.h
	g++ -c main.cpp -lncurses
game.o : game.cpp game.h menu.h sect_play.h
	g++ -c game.cpp -lncurses
sect_play.o: sect_play.cpp sect_play.h mine.h gametime.h
	g++ -c sect_play.cpp -lncurses
menu.o: menu.cpp menu.h 
	g++ -c menu.cpp -lnurses
gametime.o: gametime.cpp gametime.h
	g++ -c gametime.cpp
mine.o: mine.cpp mine.h 
	g++ -c mine.cpp
clean:
	rm *.o
