// TRON-Roguelike TimeObject.cc

#include "timeobject.hh"
#include "controlobject.hh"
#include "mapobject.hh"
#include "game.hh"
#include "serializer.hh"


TimeObject::TimeObject(uint16_t _speed)
	: id_(0), speed_(_speed), time_(0), mapobject_(NULL), controlobject_(NULL) {}

void TimeObject::Tick()
{
	if(controlobject_ != NULL)
	{
		ControlObjectMove move = controlobject_->NextMove();

		if(move.time_ < time_)
		{
			ControlObjectMove move = controlobject_->Move();
			time_ -= move.time_;
		}
	}

	if(mapobject_ != NULL)
	{
		MapObjectMove move = mapobject_->NextTick();

		if(move.time_ < time_)
		{
			mapobject_->Tick();
			time_ -= move.time_;
		}
	}
}