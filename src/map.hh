// Roguelike EngineX Map.hh

#ifndef ENGINE_XMAP_HH
#define ENGINE_XMAP_HH

#include <vector>
#include <memory>
#include <cstdint>

#include "object.hh"
#include "coord2.hh"
#include "maptile.hh"
#include "tiletype.hh"

#define NULL __null

class Map : public Object
{
  private:

  public:  
	Map();

  	void Save(std::stringstream &_save);
  	void Load() {};

	virtual void Gen(uint8_t z, uint8_t y, uint8_t x);

	inline bool CoordValid(Coord2<uint8_t> _coord) { if(_coord.x > x_ || _coord.y > y_) { return 0; } return 1; };
	inline std::shared_ptr<MapTile> Tile(Coord2<uint8_t> _coord) { return CoordValid(_coord) ? tile_[_coord.x][_coord.y] : NULL; };

	uint8_t x_;
	uint8_t y_;
	uint8_t z_;
	uint8_t size_;

	std::vector<std::vector<std::shared_ptr<MapTile> > > tile_;
	std::shared_ptr<TileType> kGround;
};

#endif
