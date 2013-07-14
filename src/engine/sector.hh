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

	std::shared_ptr<MapTile> Tile(Vector2<int16_t> _coord);
	virtual void Generate(std::shared_ptr<Sector> _this, AxisAligned_Rectangle2<int16_t> _rectangle);

	AxisAligned_Rectangle2<int16_t> rectangle_;
	std::vector<std::vector<std::shared_ptr<MapTile> > > tile_;
	std::shared_ptr<TileType> kGround;
};

class SectorGenerator : public TimeObject
{
  public:
	bool Tick();
};


#endif // TRON_RLENGINEX_SECTOR_HH
