// TRON RLengineX Sector.hh

#ifndef TRON_RLENGINEX_SECTOR_HH
#define TRON_RLENGINEX_SECTOR_HH

#include "math/axisaligned_rectangle2.hh"

#include "timeobject.hh"
#include "tiletype.hh"

#include <vector>
#include <memory>

class MapTile;

class Sector
{
  public:
	Sector();
	virtual ~Sector() {};

	MapTile* Tile(Vector2<int16_t> _coord);
	virtual void Generate(AxisAligned_Rectangle2<int16_t> _rectangle);

	AxisAligned_Rectangle2<int16_t> rectangle_;
	std::vector<std::vector<std::unique_ptr<MapTile>>> tile_;
	TileType kGround;
};

class SectorGenerator : public TimeObject
{
  public:
  	virtual ~SectorGenerator() {};
	bool Tick();
};


#endif // TRON_RLENGINEX_SECTOR_HH
