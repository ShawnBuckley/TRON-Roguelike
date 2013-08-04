// TRON-Roguelike LightWall.hh

#ifndef TRON_RLENGINEX_LIGHTWALL_HH
#define TRON_RLENGINEX_LIGHTWALL_HH

#include "engine/mapobject.hh"
#include "engine/displayobject.hh"

class Bike;

class LightWall : public MapObject
{
  public:
	LightWall() : bike_(NULL) {};
	LightWall(DisplayObject* _displayobject, MapLocation _location, uint64_t _time_dropped, Bike *_bike);

	void Serialize(YAML::Emitter& out);
	
	Bike *bike_;
	uint64_t time_dropped_;
};

#endif // TRON_RLENGINEX_LIGHTWALL_HH
