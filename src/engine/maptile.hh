// TRON-Roguelike MapTile.cc

#ifndef TRON_RLENGINEX_MAPTILE_HH
#define TRON_RLENGINEX_MAPTILE_HH

#include <cstdio>
#include <string>

#include <memory>
#include <list>

#include "math/vector2.hh"

#include "tiletype.hh"

namespace YAML
{
	class Emitter;
	class Node;
};

class DisplayObject;
class MapObject;
class Sector;
class Serializer;

class MapTile
{
  public:
	MapTile() {};
	MapTile(Vector2<int16_t> _location, Sector* _sector, TileType* _tiletype)
		: location_(_location), sector_(_sector), tiletype_(_tiletype) {};
	MapTile(const YAML::Node& in);

	bool Empty() { return mapobject_list_.empty(); }
	
	std::vector<MapObject*> SolidMapObject();
	bool AnySolidMapObject();
	DisplayObject* VisibleMapObject();


	Vector2<int16_t> location_;
	Sector* sector_;
	TileType* tiletype_;
	std::list<MapObject*> mapobject_list_;

	friend class Serializer;
};

#endif // TRON_RLENGINEX_MAPTILE_HH
