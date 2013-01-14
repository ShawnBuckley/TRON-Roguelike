// TRON-Rogulike MapObject.hh

#ifndef TRON_RLENGINEX_MAPOBJECT_HH
#define TRON_RLENGINEX_MAPOBJECT_HH

#include <cstdio>
#include <cstdint>
#include <memory>

#include "math/vector2.hh"

#include "object.hh"
#include "timeobject.hh"
#include "displayobject.hh"
#include "color.hh"

class DisplayObject;
class Color;
class Bike;
class LightWall;
class MapTile;

struct MapObjectFlags
{
	MapObjectFlags() : rez_(0), clipping_(0), visible_(0) {};
	MapObjectFlags(bool _rez, bool _clipping, bool _solid, bool _visible) : rez_(_rez), clipping_(_clipping), solid_(_solid), visible_(_visible) {};

	bool rez_;
	bool clipping_;
	bool solid_;
	bool visible_;
};

class MapObject : public Object
{
  public:
	MapObject();
	MapObject(
		std::shared_ptr<MapObject> _this,
		MapObjectFlags _mapobject_flags,
		std::shared_ptr<DisplayObject> _displayobject,
		std::shared_ptr<TimeObject> _timeobject,
		std::shared_ptr<MapTile> _maptile,
		Vector2<int16_t> _vector = Vector2<int16_t>(+0,+0)
	);
	~MapObject();

 	virtual void Save(std::stringstream &_save);
  	virtual void Load() {};

	virtual bool Rez(std::shared_ptr<MapTile> _maptile, Vector2<int16_t> _velocity = Vector2<int16_t>(+0,+0));
	virtual void Derez();

	void MapLink();
	void MapUnlink();

	virtual bool Move(Vector2<int16_t> _vector);
	bool SetLocation(std::shared_ptr<MapTile> _tile);

	virtual bool Tick();

	virtual bool CheckBump(MapObject *_mapobject) { printf("%p mapobject double dispatch call - bump\n", this); return _mapobject->DoubleDispatch_CheckBump(this); };
	virtual bool DoubleDispatch_CheckBump(MapObject *_mapobject) { printf("%p DD MO bump MO\n",this); return 1; };
	virtual bool DoubleDispatch_CheckBump(Bike *_bike) { printf("%p DD MO bump BK\n",this); return 1; };
	virtual bool DoubleDispatch_CheckBump(LightWall *_lightwall) { printf("%p DD MO bump LW\n",this); return 1; };

	virtual bool CheckBumped(MapObject *_mapobject) { printf("%p mapobject double dispatch call - check bumped\n", this); return _mapobject->DoubleDispatch_CheckBumped(this); };
	virtual bool DoubleDispatch_CheckBumped(MapObject *_mapobject) { printf("%p DD MO check MO\n",this); return 1; };
	virtual bool DoubleDispatch_CheckBumped(Bike *_bike) { printf("%p DD MO check BK\n",this); return 1; };
	virtual bool DoubleDispatch_CheckBumped(LightWall *_lightwall) { printf("%p DD MO check LW\n",this); return 1; };


	bool linked_;
	std::shared_ptr<MapTile> maptile_;
	Vector2<int16_t> vector_;
	MapObjectFlags flags_;
	std::shared_ptr<TimeObject> timeobject_;
	std::shared_ptr<DisplayObject> displayobject_;
};

#endif // TRON_RLENGINEX_OBJECT_HH
