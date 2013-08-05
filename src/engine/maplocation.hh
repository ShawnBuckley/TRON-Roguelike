// TRON-Rogulike MapLocation.hh

#ifndef TRON_RLENGINEX_MAPLOCATION_HH
#define TRON_RLENGINEX_MAPLOCATION_HH

#include <vector>

#include "math/axisaligned_rectangle2.hh"

namespace YAML
{
	class Emitter;
	class Node;
}

class MapTile;

class MapLocation
{
  public:
	MapLocation() {};
	MapLocation(AxisAligned_Rectangle2<int16_t> _rectangle);
	MapLocation(const YAML::Node& in);

	void Serialize(YAML::Emitter& out);

	std::vector<std::vector<MapTile*>> maptile_;
	AxisAligned_Rectangle2<int16_t> rectangle_;

  	void Connect();
};

#endif // TRON_RLENGINEX_MAPLOCATION_HH

