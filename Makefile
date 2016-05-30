all: aibike.o bike.o game.o gametime.o gl.o lightgrid.o lightwall.o linux.o log.o main.o map.o maplocation.o mapobject.o maptile.o player.o sdl.o sector.o serializer.o timeobject.o tron.o tronserializer.o worldtime.o
	g++ -ggdb -O2 *.o -lSDL -lpng -lGL -lyaml-cpp -o engine -std=c++0x

aibike.o: src/aibike.cc
	g++ -c src/aibike.cc -std=c++0x

bike.o: src/bike.cc
	g++ -c src/bike.cc -std=c++0x

game.o: src/engine/game.cc
	g++ -c src/engine/game.cc -std=c++0x

gametime.o: src/engine/gametime.cc
	g++ -c src/engine/gametime.cc -std=c++0x

gl.o: src/engine/gl.cc
	g++ -c src/engine/gl.cc -std=c++0x

lightgrid.o: src/lightgrid.cc
	g++ -c src/lightgrid.cc -std=c++0x

lightwall.o: src/lightwall.cc
	g++ -c src/lightwall.cc -std=c++0x

linux.o: src/engine/linux.cc
	g++ -c src/engine/linux.cc -std=c++0x

log.o: src/engine/log.cc
	g++ -c src/engine/log.cc -std=c++0x

main.o: src/main.cc
	g++ -c src/main.cc -std=c++0x

map.o: src/engine/map.cc
	g++ -c src/engine/map.cc -std=c++0x

maplocation.o: src/engine/maplocation.cc
	g++ -c src/engine/maplocation.cc -std=c++0x

mapobject.o: src/engine/mapobject.cc
	g++ -c src/engine/mapobject.cc -std=c++0x

maptile.o: src/engine/maptile.cc
	g++ -c src/engine/maptile.cc -std=c++0x

player.o: src/engine/player.cc
	g++ -c src/engine/player.cc -std=c++0x

sdl.o: src/engine/sdl.cc
	g++ -c src/engine/sdl.cc -std=c++0x

sector.o: src/engine/sector.cc
	g++ -c src/engine/sector.cc -std=c++0x

serializer.o: src/engine/serializer.cc
	g++ -c src/engine/serializer.cc -std=c++0x

timeobject.o: src/engine/timeobject.cc
	g++ -c src/engine/timeobject.cc -std=c++0x

tron.o: src/tron.cc
	g++ -c src/tron.cc -std=c++0x

tronserializer.o: src/tronserializer.cc
	g++ -c src/tronserializer.cc -std=c++0x

worldtime.o: src/engine/worldtime.cc
	g++ -c src/engine/worldtime.cc -std=c++0x

clean:
	rm -f *.o
	rm -f engine
