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
void GameTime::GameTurn(uint16_t _time)
{
	if(TimeObject::timeobjects_.empty())
		return;

	uint16_t fastest_speed = 65535;
	uint16_t tick_counts;
	uint16_t time_remainder;

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

	// bug if time is smaller than fastest speed
	tick_counts = _time / fastest_speed;
	time_remainder = !tick_counts ? _time : _time % fastest_speed;

	printf("time %i / fastest_speed %i = counts %i, remainder %i\n", _time, fastest_speed, tick_counts, time_remainder);

	for(int i=0; i<tick_counts; ++i)
	{
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
	}

	if(time_remainder > 0)
	{
		printf("remainder\n");
		tick_ += time_remainder;

		for(TimeObject* timeobject : TimeObject::timeobjects_)
		{
			timeobject->time_ += time_remainder;
			printf("%p %i\n", timeobject, timeobject->time_);
		}
	}
}