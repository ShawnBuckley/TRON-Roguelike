// TRON-Roguelike TimeObject.cc

#include "timeobject.hh"
#include "controlobject.hh"
#include "mapobject.hh"


std::list<TimeObject*> TimeObject::timeobjects_;

TimeObject::TimeObject(uint16_t _speed)
	: speed_(_speed), time_(0) {}

TimeObject::TimeObject(uint16_t _speed, std::shared_ptr<MapObject> _mapobject,
	std::shared_ptr<ControlObject> _controlobject) : speed_(_speed), time_(0) {}

TimeObject::~TimeObject()
{
	if(linked_)
		TimeUnlink();
}

void TimeObject::TimeLink()
{
	printf("Time link %p, %i\n", this, speed_);

	TimeObject::timeobjects_.push_back(this);
	
	linked_ = 1;
}

void TimeObject::TimeUnlink()
{
	printf("Time unlink %p\n", this);
/*
	for(auto it = TimeObject::timeobjects_.begin(); it != TimeObject::timeobjects_.end(); ++it)
	{
		if(*it == this)
		{
			TimeObject::timeobjects_.erase(it, it+1);
		}
	}
*/
	TimeObject::timeobjects_.remove(this);

	linked_ = 0;
}

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