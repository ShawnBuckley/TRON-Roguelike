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

namespace YAML
{
	class Emitter;
	class Node;
};

class DisplayObject;
class Color;
class MapTile;
class Serializer;

struct MapObjectStats
{
	MapObjectStats() : mass_(81647), health_(100) {};
	MapObjectStats(uint32_t _mass, uint16_t _health) : mass_(_mass), health_(_health) {};
	MapObjectStats(const YAML::Node& in);

	void Serialize(Serializer& out);

	uint32_t mass_;

	uint16_t health_;

	friend class Serializer;
};

struct MapObjectFlags
{
	MapObjectFlags() : rez_(0), clipping_(0), visible_(0) {};
	MapObjectFlags(bool _rez, bool _clipping, bool _solid, bool _visible)
	: rez_(_rez), clipping_(_clipping), solid_(_solid), visible_(_visible) {};
	MapObjectFlags(const YAML::Node& in);

	void Serialize(Serializer& out);

	bool rez_;
	bool clipping_;
	bool solid_;
	bool visible_;

	friend class Serializer;
};

class MapObjectMove
{
public:
  	MapObjectMove() : time_(0) {};
  	MapObjectMove(uint16_t _time, Vector2<int16_t> _vector) : time_(_time), vector_(_vector) {};
  	MapObjectMove(const YAML::Node& in);

  	void Serialize(Serializer& out);

	uint16_t time_;
	Vector2<int16_t> vector_;

	friend class Serializer;
};

class MapObject
{
  public:
  	static std::size_t mapobject_type_;

	MapObject() : linked_(0) {};
	MapObject(
		MapObjectStats _stats,
		MapObjectFlags _flags,
		DisplayObject* _displayobject
	) : stats_(_stats), flags_(_flags), displayobject_(_displayobject) {};
	MapObject(const YAML::Node& in);
	virtual ~MapObject();

	virtual void PRINT() { printf("MapObject\n"); };
	virtual void Serialize(Serializer& out);

	virtual bool Rez(MapLocation _location, Vector2<int16_t> _velocity = Vector2<int16_t>(+0,+0));
	virtual void Derez();

	void MapLink();
	void MapUnlink();

	virtual bool Move(MapObjectMove _move) {};
	virtual bool Move(Vector2<int16_t> _vector);
	bool SetLocation(MapLocation _location);

	virtual MapObjectMove NextTick() { return MapObjectMove(timeobject_.speed_, vector_); };
	virtual uint16_t Tick();


	uint16_t id_;
	bool linked_;

	MapLocation location_;
	Vector2<int16_t> vector_;
	std::list<MapObjectMove> moves_;

	MapObjectStats stats_;
	MapObjectFlags flags_;

	TimeObject timeobject_;
	DisplayObject* displayobject_;

	friend class Serializer;
};

#endif // TRON_RLENGINEX_OBJECT_HH
