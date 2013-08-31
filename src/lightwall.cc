// TRON-Roguelike LightWall.cc

#include "tronserializer.hh"
#include "lightwall.hh"
#include "bike.hh"

#include "engine/game.hh"
#include "engine/maptile.hh"

LightWall::LightWall(DisplayObject* _displayobject, uint64_t _time_dropped, Bike *_bike)
{
	displayobject_ = _displayobject;
	stats_ = MapObjectStats(453592, 1000);
	flags_ = MapObjectFlags(1, 1, 1, 1);
	time_dropped_ = _time_dropped;
	bike_ = _bike;
};

void LightWall::Serialize(Serializer& out)
{
	TronSerializer& tron_out = (TronSerializer&)out;
	tron_out.Serialize(*this);
}