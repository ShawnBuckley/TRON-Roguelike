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

class Bike : public MapObject
{
  public:
	Bike(MapObjectFlags _mapobject_flags, uint8_t _color, TimeObject _timeobject);
	~Bike();

	virtual void Serialize(YAML::Emitter& out);

 	void Save(std::stringstream &_save);
  	void Load() {};

  	bool Rez(MapLocation _location, Vector2<int16_t> _velocity = Vector2<int16_t>(+0,+0));
	void Derez();

	bool Move(Vector2<int16_t> _vector);

	uint16_t Tick();
	void RemoveWall();


	bool moved_;
	bool drop_walls_;
	uint8_t change_direction_;
	uint64_t time_of_death_;

	std::array<DisplayObject*, 10> bike_displayobject_;
	std::array<DisplayObject*, 10> wall_displayobject_;
	// DisplayObject* bike_displayobject_[10];
	// DisplayObject* wall_displayobject_[10];

	std::list<LightWall*> wall_list_;
};

#endif // TRON_RLENGINEX_BIKE_HH
