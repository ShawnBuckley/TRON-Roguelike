// TRON-Rogulike MapLocation.hh

#ifndef TRON_RLENGINEX_MAPLOCATION_HH
#define TRON_RLENGINEX_MAPLOCATION_HH

#include <vector>

#include "math/axisaligned_rectangle2.hh"

#include "maptile.hh"

template <typename t>
class MapLocation
{
  public:
	MapLocation() {};
	MapLocation(AxisAligned_Rectangle2<t> _rectangle) : rectangle_(_rectangle)
	{
		maptile_.reserve(rectangle_.Width());
	
		for(int16_t x=0; x<=rectangle_.Width(); ++x)
		{
			std::vector<std::shared_ptr<MapTile> > row;
			row.reserve(rectangle_.Height());
			maptile_.push_back(row);
		}
	};

	std::vector<std::vector<std::shared_ptr<MapTile> > > maptile_;
	AxisAligned_Rectangle2<t> rectangle_;

 	void Save(std::stringstream &_save) {};
  	void Load() {};
};

#endif // TRON_RLENGINEX_MAPLOCATION_HH

