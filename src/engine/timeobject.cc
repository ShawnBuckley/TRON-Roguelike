// TRON-Roguelike TimeObject.cc

#include "timeobject.hh"
#include "controlobject.hh"
#include "mapobject.hh"


std::list<TimeObject*> TimeObject::timeobjects_;
uint16_t TimeObject::fastest_speed_ = 65535;

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
	printf("Time link %p\n", this);

	TimeObject::timeobjects_.push_back(this);
	
	if(TimeObject::fastest_speed_ > speed_)
		TimeObject::fastest_speed_ = speed_;

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

	if(TimeObject::fastest_speed_ == speed_)
	{
		TimeObject::fastest_speed_ = 65535;

		for(auto timeobject : TimeObject::timeobjects_)
		{
			if(timeobject->speed_ < TimeObject::fastest_speed_)
				TimeObject::fastest_speed_ = timeobject->speed_;
		}
	}

	linked_ = 0;
}
