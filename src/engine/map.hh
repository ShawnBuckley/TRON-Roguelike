// TRON-Roguelike Map.hh

#ifndef TRON_RLENGINEX_MAP_HH
#define TRON_RLENGINEX_MAP_HH

#include <vector>
#include <memory>
#include <cstdint>

#include "math/vector2.hh"
#include "math/axisaligned_rectangle2.hh"

#include "maptile.hh"
#include "tiletype.hh"

// #define NULL __null

class Map
{
  private:

  public:  
	Map() {};

	inline bool CoordValid(Vector2<int16_t>  _point) { return rectangle_.Intersect(_point); };
	std::shared_ptr<MapTile> Tile(Vector2<int16_t>  _point);

	void GenerateSector(std::shared_ptr<Sector> _sector, AxisAligned_Rectangle2<int16_t> _rectangle);

	AxisAligned_Rectangle2<int16_t> rectangle_;
	std::vector<std::shared_ptr<Sector> > sector_;
};

#endif // TRON_RLENGINEX_MAP_HH
