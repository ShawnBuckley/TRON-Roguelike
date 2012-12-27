// Roguelike EngineX MapTile.cc

#ifndef ENGINE_MAPTILE_HH
#define ENGINE_MAPTILE_HH

#include <cstdio>
#include <string>

#include <memory>
#include <list>

#include "coord2.hh"
#include "object.hh"
#include "tiletype.hh"

class MapObject;
class DisplayObject;

class MapTile : public Object
{
  public:
	MapTile() {};
	MapTile(Coord2<uint8_t> _location, std::shared_ptr<TileType> _tiletype) : location_(_location), tiletype_(_tiletype) {};

	void Save(std::stringstream &_save);
	void Load() {};

	bool Empty() { return mapobject_list_.empty(); }
	
	MapObject* SolidMapObject();
	std::shared_ptr<DisplayObject> VisibleMapObject();

	Coord2<uint8_t> location_;
	std::shared_ptr<TileType> tiletype_;
	std::list<MapObject*> mapobject_list_;
};

#endif
