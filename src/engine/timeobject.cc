// TRON-Roguelike TimeObject.cc

#include "timeobject.hh"
#include "controlobject.hh"
#include "mapobject.hh"
#include "game.hh"


std::list<TimeObject*> TimeObject::timeobjects_;


TimeObject::TimeObject(uint16_t _speed)
	: speed_(_speed), time_(0) {}

TimeObject::TimeObject(const YAML::Node& in)
{
	linked_ = in["linked"].as<bool>();
	speed_ = in["speed"].as<int>();
	time_ = in["speed"].as<int>();

	uint16_t mapobject = in["mapobject"].as<int>();
	if(mapobject >= 0)
		mapobject_ = game().GetMapObject(mapobject);
	else
		mapobject_ = NULL;

	uint16_t controlobject = in["mapobject"].as<int>();
	if(mapobject >= 0)
		controlobject_ = game().GetControlObject(controlobject);
	else
		controlobject_ = NULL;

	TimeLink();
}

void TimeObject::Serialize(YAML::Emitter& out)
{
	out << YAML::BeginMap;
	out << "linked" << linked_;
	out << "speed" << (int)speed_;
	out << "time" << (int)time_;
	out << "mapobject";
	if(mapobject_)
		out << mapobject_->id_;
	else
		out << -1;
	out << "controlobject";
	if(controlobject_)
		out << controlobject_->id_;
	else
		out << -1;
	out << YAML::EndMap;
}

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