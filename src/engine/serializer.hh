// TRON-Roguelike Serializerk.hh

#ifndef TRON_RLENGINEX_SERIALIZER_HH
#define TRON_RLENGINEX_SERIALIZER_HH

#include <yaml-cpp/yaml.h>

namespace YAML
{
	class Emitter;
	class Node;
};

template<typename t>
class Vector2;

template<typename t>
class AxisAligned_Rectangle2;

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
  public:
	Serializer();
	virtual ~Serializer() {};
	YAML::Emitter& YAML() { return out; };

	void Serialize(const Vector2<int16_t> in);
	void Serialize(const AxisAligned_Rectangle2<int16_t> in);

	void Serialize(const Game& in);

	void Serialize(const ControlObjectMove& in);

	void Serialize(const DisplayObject& in);
	void Serialize(const TimeObject& in);

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

	///////////////////////////////////////////////////////////////////////////
	// 
	// Unserialize
	// 
	///////////////////////////////////////////////////////////////////////////

	template<typename t>
	Vector2<t> UnserializeVector2(const YAML::Node& in);

	template<typename t>
	AxisAligned_Rectangle2<t> UnserializeAxisAligned_Rectangle2(
		const YAML::Node& in);

	Game* UnserializeGame(const YAML::Node& in);
	IO* UnserializeIO(const YAML::Node& in);

	GameTime* UnserializeGameTime(const YAML::Node& in);
	WorldTime* UnserializeWorldTime(const YAML::Node& in);

	DisplayObject UnserializeDisplayObject(const YAML::Node& in);

	TileTypeFlags UnserializeTileTypeFlags(const YAML::Node& in);
	TileType UnserializeTileType(const YAML::Node& in);

	MapObjectFlags UnserializeMapObjectFlags(const YAML::Node& in);
	MapObjectStats UnserializeMapObjectStats(const YAML::Node& in);
	MapObjectMove UnserializeMapObjectMove(const YAML::Node& in);
	MapLocation UnserializeMapLocation(const YAML::Node& in);
	TimeObject* UnserializeTimeObject(const YAML::Node& in);
	MapObject* UnserializeMapObject(const YAML::Node& in);

	ControlObjectMove UnserializeControlObjectMove(const YAML::Node& in);
	Player* UnserializePlayer(const YAML::Node& in);

	Map* UnserializeMap(const YAML::Node& in);

	///////////////////////////////////////////////////////////////////////////
	// 
	// Load / Reassemble
	// 
	///////////////////////////////////////////////////////////////////////////

	void LoadGameTime(const YAML::Node& in);
	void LoadDisplayObjects(const YAML::Node& in);
	
	void LoadTileTypes(const YAML::Node& in);
	virtual void LoadMapObjects(const YAML::Node& in);
	
	virtual void LoadControlObjects(const YAML::Node& in);
	void LoadTimeObjects(const YAML::Node& in);
	void LoadMap(const YAML::Node& in);
	virtual void LoadSectors(const YAML::Node& in);
	void LoadMapLoactions(const YAML::Node& in);

  protected:
	YAML::Emitter out;

  friend class Game;
};

template<typename t>
Vector2<t> Serializer::UnserializeVector2(const YAML::Node& in)
{
	return Vector2<t>(in[0].as<t>(), in[1].as<t>());
}

template<typename t>
AxisAligned_Rectangle2<t> Serializer::UnserializeAxisAligned_Rectangle2(
	const YAML::Node& in)
{
	return AxisAligned_Rectangle2<t>(
		Vector2<t>(in[0].as<int>(), in[1].as<int>()),
		in[2].as<int>(), in[3].as<int>());
}

#endif