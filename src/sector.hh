// TRON RLengineX Sector.hh

#ifndef TRON_RLENGINEX_SECTOR_HH
#define TRON_RLENGINEX_SECTOR_HH

#include "math/axisaligned_rectangle2.hh"

#include "object.hh"
#include "timeobject.hh"

#include <vector>
#include <memory>

class MapTile;

class Sector : public Object
{
  public:
	Sector();

	void Save(std::stringstream &_save) {};
	void Load() {};

	std::shared_ptr<MapTile> Tile(Vector2<int16_t> _coord)
	{
		if(0 <= _coord.x() && _coord.x() <=rectangle_.Width() && 0 <= _coord.y() && _coord.y() <= rectangle_.Height())
		{
			return tile_[_coord.x()][_coord.y()];
		}

		return NULL;
	};

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
