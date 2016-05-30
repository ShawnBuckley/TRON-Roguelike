CC = g++
STD = c++11

OBJ_DIR = obj
_OBJ = aibike.o bike.o game.o gametime.o gl.o lightgrid.o lightwall.o linux.o log.o main.o map.o maplocation.o mapobject.o maptile.o player.o sdl.o sector.o serializer.o timeobject.o tron.o tronserializer.o worldtime.o
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

EXECUTABLE = tron

all: $(OBJ_DIR) $(OBJ)
	$(CC) -ggdb -O2 $(OBJ) -lSDL -lpng -lGL -lyaml-cpp -o $(EXECUTABLE) -std=$(STD)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/aibike.o: src/aibike.cc
	$(CC) -c src/aibike.cc -o $(OBJ_DIR)/aibike.o -std=$(STD)

$(OBJ_DIR)/bike.o: src/bike.cc
	$(CC) -c src/bike.cc -o $(OBJ_DIR)/bike.o -std=$(STD)

$(OBJ_DIR)/game.o: src/engine/game.cc
	$(CC) -c src/engine/game.cc -o $(OBJ_DIR)/game.o -std=$(STD)

$(OBJ_DIR)/gametime.o: src/engine/gametime.cc
	$(CC) -c src/engine/gametime.cc -o $(OBJ_DIR)/gametime.o -std=$(STD)

$(OBJ_DIR)/gl.o: src/engine/gl.cc
	$(CC) -c src/engine/gl.cc -o $(OBJ_DIR)/gl.o -std=$(STD)

$(OBJ_DIR)/lightgrid.o: src/lightgrid.cc
	$(CC) -c src/lightgrid.cc -o $(OBJ_DIR)/lightgrid.o -std=$(STD)

$(OBJ_DIR)/lightwall.o: src/lightwall.cc
	$(CC) -c src/lightwall.cc -o$(OBJ_DIR)/lightwall.o -std=$(STD)

$(OBJ_DIR)/linux.o: src/engine/linux.cc
	$(CC) -c src/engine/linux.cc -o $(OBJ_DIR)/linux.o -std=$(STD)

$(OBJ_DIR)/log.o: src/engine/log.cc
	$(CC) -c src/engine/log.cc -o $(OBJ_DIR)/log.o -std=$(STD)

$(OBJ_DIR)/main.o: src/main.cc
	$(CC) -c src/main.cc -o $(OBJ_DIR)/main.o -std=$(STD)

$(OBJ_DIR)/map.o: src/engine/map.cc
	$(CC) -c src/engine/map.cc -o $(OBJ_DIR)/map.o -std=$(STD)

$(OBJ_DIR)/maplocation.o: src/engine/maplocation.cc
	$(CC) -c src/engine/maplocation.cc -o $(OBJ_DIR)/maplocation.o -std=$(STD)

$(OBJ_DIR)/mapobject.o: src/engine/mapobject.cc
	$(CC) -c src/engine/mapobject.cc -o $(OBJ_DIR)/mapobject.o -std=$(STD)

$(OBJ_DIR)/maptile.o: src/engine/maptile.cc
	$(CC) -c src/engine/maptile.cc -o $(OBJ_DIR)/maptile.o -std=$(STD)

$(OBJ_DIR)/player.o: src/engine/player.cc
	$(CC) -c src/engine/player.cc -o $(OBJ_DIR)/player.o -std=$(STD)

$(OBJ_DIR)/sdl.o: src/engine/sdl.cc
	$(CC) -c src/engine/sdl.cc -o $(OBJ_DIR)/sdl.o -std=$(STD)

$(OBJ_DIR)/sector.o: src/engine/sector.cc
	$(CC) -c src/engine/sector.cc -o $(OBJ_DIR)/sector.o -std=$(STD)

$(OBJ_DIR)/serializer.o: src/engine/serializer.cc
	$(CC) -c src/engine/serializer.cc -o $(OBJ_DIR)/serializer.o -std=$(STD)

$(OBJ_DIR)/timeobject.o: src/engine/timeobject.cc
	$(CC) -c src/engine/timeobject.cc -o $(OBJ_DIR)/timeobject.o -std=$(STD)

$(OBJ_DIR)/tron.o: src/tron.cc
	$(CC) -c src/tron.cc -o $(OBJ_DIR)/tron.o -std=$(STD)

$(OBJ_DIR)/tronserializer.o: src/tronserializer.cc
	$(CC) -c src/tronserializer.cc -o $(OBJ_DIR)/tronserializer.o -std=$(STD)

$(OBJ_DIR)/worldtime.o: src/engine/worldtime.cc
	$(CC) -c src/engine/worldtime.cc -o $(OBJ_DIR)/worldtime.o -std=$(STD)

clean:
	rm -f $(OBJ)
	rm -f $(EXECUTABLE)
