// TRON-Roguelike xBike.hh

#ifndef TRON_RLENGINEX_BIKE_HH
#define TRON_RLENGINEX_BIKE_HH

#include <inttypes.h>

#include <memory>
#include <list>
#include <vector>
#include <array>

#include "engine/math/vector2.hh"
#include "engine/mapobject.hh"

#include "lightwall.hh"

class Color;

struct BikeFlags
{
	BikeFlags() : drop_walls_(1) {};

	bool drop_walls_;
};

class Bike : public MapObject
{
  public:
	Bike(MapObjectFlags _mapobject_flags, uint8_t _color, TimeObject _timeobject);
	~Bike();

 	void Save(std::stringstream &_save);
  	void Load() {};

  	bool Rez(MapLocation<int16_t> _location, Vector2<int16_t> _velocity = Vector2<int16_t>(+0,+0));
	void Derez();

	bool Move(Vector2<int16_t> _vector);

	uint16_t Tick();
	void RemoveWall();


	bool moved_;
	uint8_t change_direction_;
	uint64_t time_of_death_;
	BikeFlags bike_flags_;

	std::array<DisplayObject*, 10> bike_displayobject_;
	std::array<DisplayObject*, 10> wall_displayobject_;
	// DisplayObject* bike_displayobject_[10];
	// DisplayObject* wall_displayobject_[10];

	std::list<std::unique_ptr<LightWall>> wall_list_;
};

#endif // TRON_RLENGINEX_BIKE_HH
