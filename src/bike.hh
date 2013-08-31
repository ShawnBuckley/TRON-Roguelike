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

namespace YAML
{
	class Emitter;
	class Node;
}

class Color;

class TronSerializer;

class Bike : public MapObject
{
  public:
	Bike(MapObjectFlags _mapobject_flags, uint8_t _color, TimeObject* _timeobject);
	Bike(const YAML::Node& in);
	~Bike();

	virtual void Serialize(Serializer& out);

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

	std::list<LightWall*> wall_list_;

	Bike(uint16_t _id, bool _linked, bool _moved, bool _drop_walls_, uint8_t _change_direction,
		uint64_t _time_of_death, DisplayObject* _displayobject,
		MapObjectStats _stats, MapObjectFlags _flags, MapLocation _location,
		Vector2<short int> _vector,
		std::array<DisplayObject*, 10> _bike_displayobject,
		std::array<DisplayObject*, 10> _wall_displayobject,
		std::list<MapObjectMove> _moves) : moved_(_moved), drop_walls_(_drop_walls_),
			change_direction_(_change_direction), time_of_death_(_time_of_death),
			bike_displayobject_(_bike_displayobject),
			wall_displayobject_(_wall_displayobject)
	{
		id_ = _id;
		linked_ = _linked;
		displayobject_ = _displayobject;
		stats_ = _stats;
		flags_ = _flags;
		location_ = _location;
		vector_ = _vector;
		moves_ = _moves;
	}
};

#endif // TRON_RLENGINEX_BIKE_HH
