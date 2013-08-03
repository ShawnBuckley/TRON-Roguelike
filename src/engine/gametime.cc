// TRON-Roguelike GameTime.hh

#include <stdio.h>

#include <algorithm>

#include "gametime.hh"
#include "mapobject.hh"
#include "timeobject.hh"
#include "controlobject.hh"

GameTime::GameTime()
{
	tick_ = 0;
}

// TODO TimeObjects schedule in timeactions, which then execute
uint16_t GameTime::Turn()
{
	if(TimeObject::timeobjects_.empty())
		return 0;

	uint16_t fastest_speed = 65535;

	// think loop
	for(TimeObject* timeobject : TimeObject::timeobjects_)
	{
		if(timeobject)
		{
			if(timeobject->mapobject_)
			{
				MapObjectMove move = timeobject->mapobject_->NextTick();

				if(move.time_ < fastest_speed && move.time_ > 0)
				{
					fastest_speed = move.time_;
				}
			}

			if(timeobject->controlobject_)
			{
				ControlObjectMove move = timeobject->controlobject_->NextMove();

				if(move.time_ < fastest_speed && move.time_ > 0)
				{
					fastest_speed = move.time_;
				}
			}
		}
	}

	tick_ += fastest_speed;

	// Tick loop
	for(auto it = TimeObject::timeobjects_.begin(); it != TimeObject::timeobjects_.end();)
	{
		TimeObject* timeobject = *it;
		++it;

		if(timeobject == NULL || !timeobject->linked_ || !timeobject->speed_) continue;

		timeobject->time_ += fastest_speed;
		timeobject->Tick();
	}

	return fastest_speed;
}