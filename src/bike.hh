// TRON-Roguelike xBike.hh

#ifndef TRON_RLENGINEX_BIKE_HH
#define TRON_RLENGINEX_BIKE_HH

#include <inttypes.h>

#include <memory>
#include <list>
#include <vector>

#include "math/vector2.hh"

#include "mapobject.hh"

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
  	Bike(std::shared_ptr<Color> _color);	
	Bike(std::shared_ptr<MapObject> _this, MapObjectFlags _mapobject_flags, std::shared_ptr<DisplayObject> _displayobject, std::shared_ptr<TimeObject> _timeobject, Vector2<uint8_t> _location, Vector2<int8_t> _vector = Vector2<int8_t>(+0,+0));
	~Bike();

 	void Save(std::stringstream &_save);
  	void Load() {};

	void Derez();

	bool Move(Vector2<int16_t> _vector);

	bool Tick();
	void RemoveWall();

	bool CheckBump(MapObject *_mapobject) { printf("%p mapobject double dispatch call - bumped\n", this); return _mapobject->DoubleDispatch_CheckBump(this); };
	bool DoubleDispatch_CheckBump(MapObject *_mapobject) { printf("%p DD BK bumped MO\n",this); return 1; };
	bool DoubleDispatch_CheckBump(Bike *_bike) { printf("%p DD BK bumped BK\n",this); return 1; };
	bool DoubleDispatch_CheckBump(LightWall *_lightwall) { printf("%p DD BK bumped LW\n",this); return 1; };

	bool CheckBumped(MapObject *_mapobject) { printf("bike double dispatch call\n"); return _mapobject->DoubleDispatch_CheckBumped(this); };
	bool DoubleDispatch_CheckBumped(MapObject *_mapobject) { printf("%p DD BK check MO\n",this); return 0; };
	bool DoubleDispatch_CheckBumped(Bike *_bike) { printf("%p DD BK check BK\n",this); return 1; };
	bool DoubleDispatch_CheckBumped(LightWall *_lightwall) { printf("%p DD BK check LW\n",this); return 1; };

	bool moved_;
	int change_direction_;
	BikeFlags bike_flags_;

	std::list<std::shared_ptr<LightWall> > wall_list_;
	std::shared_ptr<DisplayObject> wall_displayobject_[10];
};

#endif // TRON_RLENGINEX_BIKE_HH
