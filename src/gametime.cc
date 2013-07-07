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

void GameTime::Save(std::stringstream &_save)
{
	_save << "gametime" << " "
		<< "a" << " "
		<< (unsigned int)id_ << " "
		<< (unsigned int)tick_ << " "
		<< std::endl;
}

// TODO TimeObjects schedule in timeactions, which then execute
void GameTime::GameTurn(uint16_t _time)
{
	uint16_t tick_counts = _time / TimeObject::fastest_speed_;
	uint16_t time_remainder = _time % TimeObject::fastest_speed_;

	for(int i=0; i<tick_counts; ++i)
	{
		tick_ += TimeObject::fastest_speed_;

		// Think loop
		for(TimeObject* timeobject : TimeObject::timeobjects_)
		{
			if(timeobject == NULL) continue;

			timeobject->time_ += TimeObject::fastest_speed_;

			if(timeobject->controlobject_ && timeobject->time_)
			{
				timeobject->controlobject_->Think(timeobject->time_);
			}
		}

		// Tick loop
		for(auto it = TimeObject::timeobjects_.begin(); it != TimeObject::timeobjects_.end();)
		{
			// ensures that the position isn't lost if the entity dies and time unlinks during its turn
			TimeObject* timeobject = *it;
			++it;

			if(timeobject == NULL) continue;

			if(timeobject->controlobject_ != NULL)
			{
				ControlObjectMove next_move;

				while(timeobject->controlobject_->HasNextMove())
				{
					ControlObjectMove move = timeobject->controlobject_->Move();
					timeobject->time_ -= move.time_;
					next_move = (timeobject->controlobject_->NextMove());
				}
			}
			
			if(timeobject->speed_)
			{
				while(timeobject->time_ > timeobject->speed_)
				{
					if(timeobject->mapobject_ && timeobject->linked_)
						timeobject->time_ -= timeobject->mapobject_->Tick();
					else
						break;
				}
			}
		}
	}

	if(time_remainder > 0)
	{
		tick_ += time_remainder;

		for(TimeObject* timeobject : TimeObject::timeobjects_)
		{
			timeobject->time_ += time_remainder;
		}
	}
}