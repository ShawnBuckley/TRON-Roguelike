all:
	g++ -c src/*.cc -std=c++0x
	g++ -ggdb -O2 *.o -lcurses -lSDL -lpng -lGL -o engine -std=c++0x

clean:
	rm -f *.o
	rm -f engine
