// TRON-Roguelike Serializerk.hh

#ifndef TRON_RLENGINEX_TRON_HH
#define TRON_RLENGINEX_TRON_HH

#include <yaml-cpp/yaml.h>

namespace YAML
{
	class Emitter;
	class Node;
};

class ControlObjectMove;
class ControlObject;

class Game;

class GameTime;

class IO;

class DisplayObject;
class TimeObject;

class Map;

class MapLocation;
class MapObjectStats;
class MapObjectFlags;
class MapObjectMove;
class MapObject;

class MapTile;

class Player;

class TileTypeFlags;
class TileType;

class Sector;

class WorldTime;



class Serializer
{
  protected:
	YAML::Emitter out;

  public:
	Serializer();
	YAML::Emitter& YAML() { return out; };

	void Serialize(const ControlObjectMove& in);

	void Serialize(const DisplayObject& in);
	void Serialize(const TimeObject& in);

	void Serialize(const Game& in);

	void Serialize(const GameTime& in);

	void Serialize(const IO& in);

	void Serialize(const Map& in);

	void Serialize(const MapLocation& in); 
	void Serialize(const MapObjectStats& in);
	void Serialize(const MapObjectFlags& in);
	void Serialize(const MapObjectMove& in);
	void Serialize(const MapObject& in);

	void Serialize(const MapTile& in);

	void Serialize(const Player& in);

	void Serialize(const TileTypeFlags& in);
	void Serialize(const TileType& in);

	void Serialize(const Sector& in);

	void Serialize(const WorldTime& in);

	friend class Game;
};

#endif