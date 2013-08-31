// TRON-Roguelike GameTime.hh

#include <stdio.h>

#include <algorithm>

#include "serializer.hh"
#include "game.hh"
#include "gametime.hh"
#include "mapobject.hh"
#include "timeobject.hh"
#include "controlobject.hh"

void GameTime::Serialize(Serializer& out) const
{
	out.Serialize(*this);
}

// TODO TimeObjects schedule in timeactions, which then execute
uint16_t GameTime::Turn()
{
	printf("gametime turn\n");

	if(game().timeobjects_.empty())
		return 0;

	uint16_t fastest_speed = 65535;

	auto start = game().timeobjects_.begin();
	auto end = game().timeobjects_.end();
	printf("think loop\n");
	// think loop
	for(auto it = start; it != end; it++)
	{
		printf("start cyc %p\n", (*it).get());
		TimeObject* timeobject = (*it).get();

		if(timeobject != NULL)
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
		printf("end cyc\n");
	}
	printf("end\n");
	tick_ += fastest_speed;
	printf("tick loop\n");
	// Tick loop
	for(auto it = start; it != end; it++)
	{
		printf("tick cyc %p\n", (*it).get());
		TimeObject* timeobject = (*it).get();
		// ++it;

		if(timeobject == NULL || !timeobject->linked_ || !timeobject->speed_) { continue; }

		timeobject->time_ += fastest_speed;
		timeobject->Tick();

		printf("tick cyc\n");
	}
	printf("end\n");

	return fastest_speed;
}