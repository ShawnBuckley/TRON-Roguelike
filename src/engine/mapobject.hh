// TRON-Rogulike MapObject.hh

#ifndef TRON_RLENGINEX_MAPOBJECT_HH
#define TRON_RLENGINEX_MAPOBJECT_HH

#include <cstdio>
#include <cstdint>
#include <memory>

#include "math/vector2.hh"

#include "maplocation.hh"
#include "timeobject.hh"
#include "displayobject.hh"
#include "io.hh"

class DisplayObject;
class Color;
class MapTile;

struct MapObjectStats
{
	MapObjectStats() : mass_(81647), health_(100) {};
	MapObjectStats(uint32_t _mass, uint16_t _health) : mass_(_mass), health_(_health) {};

	uint32_t mass_;

	uint16_t health_;
};

struct MapObjectFlags
{
	MapObjectFlags() : rez_(0), clipping_(0), visible_(0) {};
	MapObjectFlags(bool _rez, bool _clipping, bool _solid, bool _visible)
	: rez_(_rez), clipping_(_clipping), solid_(_solid), visible_(_visible) {};

	bool rez_;
	bool clipping_;
	bool solid_;
	bool visible_;
};

class MapObject
{
  public:
	MapObject() : linked_(0) {};
	MapObject(
		MapObjectStats _stats,
		MapObjectFlags _flags,
		DisplayObject* _displayobject
	) : stats_(_stats), flags_(_flags), displayobject_(_displayobject) {};
	virtual ~MapObject();

	virtual bool Rez(MapLocation<int16_t> _location, Vector2<int16_t> _velocity = Vector2<int16_t>(+0,+0));
	virtual void Derez();

	void MapLink();
	void MapUnlink();

	virtual bool Move(Vector2<int16_t> _vector);
	bool SetLocation(MapLocation<int16_t> _location);

	virtual uint16_t Tick();


	uint16_t id_;
	bool linked_;
	MapLocation<int16_t> location_;
	Vector2<int16_t> vector_;

	MapObjectStats stats_;
	MapObjectFlags flags_;

	TimeObject timeobject_;
	DisplayObject* displayobject_;
};

#endif // TRON_RLENGINEX_OBJECT_HH
