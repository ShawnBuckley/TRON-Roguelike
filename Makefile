CC = g++
STD = c++11

all: aibike.o bike.o game.o gametime.o gl.o lightgrid.o lightwall.o linux.o log.o main.o map.o maplocation.o mapobject.o maptile.o player.o sdl.o sector.o serializer.o timeobject.o tron.o tronserializer.o worldtime.o
	$(CC) -ggdb -O2 *.o -lSDL -lpng -lGL -lyaml-cpp -o engine -std=$(STD)

aibike.o: src/aibike.cc
	$(CC) -c src/aibike.cc -std=$(STD)

bike.o: src/bike.cc
	$(CC) -c src/bike.cc -std=$(STD)

game.o: src/engine/game.cc
	$(CC) -c src/engine/game.cc -std=$(STD)

gametime.o: src/engine/gametime.cc
	$(CC) -c src/engine/gametime.cc -std=$(STD)

gl.o: src/engine/gl.cc
	$(CC) -c src/engine/gl.cc -std=$(STD)

lightgrid.o: src/lightgrid.cc
	$(CC) -c src/lightgrid.cc -std=$(STD)

lightwall.o: src/lightwall.cc
	$(CC) -c src/lightwall.cc -std=$(STD)

linux.o: src/engine/linux.cc
	$(CC) -c src/engine/linux.cc -std=$(STD)

log.o: src/engine/log.cc
	$(CC) -c src/engine/log.cc -std=$(STD)

main.o: src/main.cc
	$(CC) -c src/main.cc -std=$(STD)

map.o: src/engine/map.cc
	$(CC) -c src/engine/map.cc -std=$(STD)

maplocation.o: src/engine/maplocation.cc
	$(CC) -c src/engine/maplocation.cc -std=$(STD)

mapobject.o: src/engine/mapobject.cc
	$(CC) -c src/engine/mapobject.cc -std=$(STD)

maptile.o: src/engine/maptile.cc
	$(CC) -c src/engine/maptile.cc -std=$(STD)

player.o: src/engine/player.cc
	$(CC) -c src/engine/player.cc -std=$(STD)

sdl.o: src/engine/sdl.cc
	$(CC) -c src/engine/sdl.cc -std=$(STD)

sector.o: src/engine/sector.cc
	$(CC) -c src/engine/sector.cc -std=$(STD)

serializer.o: src/engine/serializer.cc
	$(CC) -c src/engine/serializer.cc -std=$(STD)

timeobject.o: src/engine/timeobject.cc
	$(CC) -c src/engine/timeobject.cc -std=$(STD)

tron.o: src/tron.cc
	$(CC) -c src/tron.cc -std=$(STD)

tronserializer.o: src/tronserializer.cc
	$(CC) -c src/tronserializer.cc -std=$(STD)

worldtime.o: src/engine/worldtime.cc
	$(CC) -c src/engine/worldtime.cc -std=$(STD)

clean:
	rm -f *.o
	rm -f engine
