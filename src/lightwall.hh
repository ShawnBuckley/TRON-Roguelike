// TRON-Roguelike LightWall.hh

#ifndef TRON_RLENGINEX_LIGHTWALL_HH
#define TRON_RLENGINEX_LIGHTWALL_HH

#include "engine/mapobject.hh"
#include "engine/displayobject.hh"

namespace YAML
{
	class Emitter;
	class Node;
}

class Bike;
class TronSerializer;

class LightWall : public MapObject
{
  public:
	LightWall() : bike_(NULL) {};
	LightWall(DisplayObject* _displayobject, uint64_t _time_dropped, Bike *_bike);
	LightWall(const YAML::Node& in);

	void Serialize(TronSerializer& out);
	
	Bike *bike_;
	uint64_t time_dropped_;

	friend class TronSerializer;
};

#endif // TRON_RLENGINEX_LIGHTWALL_HH
