// TRON-Roguelike MapTile.cc

#ifndef TRON_RLENGINEX_MAPTILE_HH
#define TRON_RLENGINEX_MAPTILE_HH

#include <cstdio>
#include <string>

#include <memory>
#include <list>

#include "math/vector2.hh"

#include "gameobject.hh"
#include "tiletype.hh"

class DisplayObject;
class MapObject;
class Sector;

class MapTile : public GameObject
{
  public:
	MapTile() {};
	MapTile(Vector2<int16_t> _location, std::shared_ptr<Sector> _sector, std::shared_ptr<TileType> _tiletype)
		: location_(_location), sector_(_sector), tiletype_(_tiletype) {};

	void Save(std::stringstream &_save);
	void Load() {};

	bool Empty() { return mapobject_list_.empty(); }
	
	std::vector<MapObject*> SolidMapObject();
	bool AnySolidMapObject();
	std::shared_ptr<DisplayObject> VisibleMapObject();


	Vector2<int16_t> location_;
	std::shared_ptr<Sector> sector_;
	std::shared_ptr<TileType> tiletype_;
	std::list<MapObject*> mapobject_list_;
};

#endif // TRON_RLENGINEX_MAPTILE_HH
