all: aibike.o bike.o color.o controlobject.o displayobject.o entitymanager.o game.o gametime.o gl.o lightgrid.o lightwall.o linux.o log.o main.o map.o mapobject.o maptile.o gameobject.o player.o sdl.o sector.o tiletype.o timeobject.o worldtime.o
	g++ -ggdb -O2 *.o -lcurses -lSDL -lpng -lGL -o engine -std=c++0x

aibike.o: src/aibike.cc
	g++ -c src/aibike.cc -std=c++0x

bike.o: src/bike.cc
	g++ -c src/bike.cc -std=c++0x

color.o: src/color.cc
	g++ -c src/color.cc -std=c++0x

controlobject.o: src/controlobject.cc
	g++ -c src/controlobject.cc -std=c++0x

displayobject.o: src/displayobject.cc
	g++ -c src/displayobject.cc -std=c++0x
	
entitymanager.o: src/entitymanager.cc
	g++ -c src/entitymanager.cc -std=c++0x

game.o: src/game.cc
	g++ -c src/game.cc -std=c++0x

gametime.o: src/gametime.cc
	g++ -c src/gametime.cc -std=c++0x

gl.o: src/gl.cc
	g++ -c src/gl.cc -std=c++0x

lightgrid.o: src/lightgrid.cc
	g++ -c src/lightgrid.cc -std=c++0x

lightwall.o: src/lightwall.cc
	g++ -c src/lightwall.cc -std=c++0x

linux.o: src/linux.cc
	g++ -c src/linux.cc -std=c++0x

log.o: src/log.cc
	g++ -c src/log.cc -std=c++0x

main.o: src/main.cc
	g++ -c src/main.cc -std=c++0x

map.o: src/map.cc
	g++ -c src/map.cc -std=c++0x

mapobject.o: src/mapobject.cc
	g++ -c src/mapobject.cc -std=c++0x

maptile.o: src/maptile.cc
	g++ -c src/maptile.cc -std=c++0x

gameobject.o: src/gameobject.cc
	g++ -c src/gameobject.cc -std=c++0x

player.o: src/player.cc
	g++ -c src/player.cc -std=c++0x

sdl.o: src/sdl.cc
	g++ -c src/sdl.cc -std=c++0x

sector.o: src/sector.cc
	g++ -c src/sector.cc -std=c++0x

tiletype.o: src/tiletype.cc
	g++ -c src/tiletype.cc -std=c++0x

timeobject.o: src/timeobject.cc
	g++ -c src/timeobject.cc -std=c++0x

worldtime.o: src/worldtime.cc
	g++ -c src/worldtime.cc -std=c++0x

clean:
	rm -f *.o
	rm -f engine
