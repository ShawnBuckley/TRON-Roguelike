// TRON-Roguelike LightWall.hh

#ifndef TRON_RLENGINEX_LIGHTWALL_HH
#define TRON_RLENGINEX_LIGHTWALL_HH

#include "engine/mapobject.hh"
#include "engine/displayobject.hh"

class Bike;
class TronSerializer;

class LightWall : public MapObject
{
  public:
	LightWall() : bike_(NULL) {};
	LightWall(DisplayObject* _displayobject, uint64_t _time_dropped, Bike *_bike);

	void Serialize(Serializer& out);
	
	Bike *bike_;
	uint64_t time_dropped_;

  private:
	LightWall(uint16_t _id, DisplayObject* _displayobject,
		MapObjectStats _stats, MapLocation _location, Bike* _bike,
		uint64_t _time_dropped) : bike_(_bike), time_dropped_(_time_dropped)
	{
		id_ = _id;
		linked_ = 1;
		displayobject_ = _displayobject;
		stats_ = _stats;
		flags_ = MapObjectFlags(1, 1, 1, 1);
	};

  friend class TronSerializer;
};

#endif // TRON_RLENGINEX_LIGHTWALL_HH
