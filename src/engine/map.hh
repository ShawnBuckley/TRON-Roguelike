// TRON-Roguelike Map.hh

#ifndef TRON_RLENGINEX_MAP_HH
#define TRON_RLENGINEX_MAP_HH

#include <vector>
#include <memory>
#include <cstdint>

#include "math/vector2.hh"
#include "math/axisaligned_rectangle2.hh"

#include "maptile.hh"
#include "sector.hh"
#include "tiletype.hh"

// #define NULL __null

class Map
{
  private:

  public:  
	Map() {};

	inline bool CoordValid(Vector2<int16_t>  _point) { return rectangle_.Intersect(_point); };
	MapTile* Tile(Vector2<int16_t>  _point);

	void AddTileType(TileType *_tiletype);
	void GenerateSector(Sector* _sector, AxisAligned_Rectangle2<int16_t> _rectangle);



	AxisAligned_Rectangle2<int16_t> rectangle_;
	std::vector<std::unique_ptr<Sector>> sector_;
	std::vector<std::unique_ptr<TileType>> tiletypes_;
};

#endif // TRON_RLENGINEX_MAP_HH
