// TRON-Roguelike GameTime.hh

#include <stdio.h>

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

void GameTime::GameTurn(uint16_t _time)
{
	TimeObject *timeobject;
	std::list<TimeObject*>::iterator it = TimeObject::list_.begin();

	tick_ += _time;

	while(it != TimeObject::list_.end())
	{
		timeobject = *it;
		++it;

		if(timeobject == NULL) continue;
		
		timeobject->time_ += _time;

		if(timeobject->speed_ && timeobject->time_ >= timeobject->speed_)
		{
			while(timeobject->time_ - timeobject->speed_ > 0)
			{
				timeobject->time_ -= timeobject->speed_;
		
				if(timeobject->mapobject_)
				{
					if(timeobject->controlobject_) timeobject->controlobject_->Think();
					if(!timeobject->mapobject_->Tick()) break;
				}
			}
		}
	}
}
