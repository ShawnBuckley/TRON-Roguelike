// TRON-Roguelike Player.cc

#include <stdio.h>

#include "player.hh"
#include "mapobject.hh"
#include "worldtime.hh"

#include "main.hh"

void Player::Save(std::stringstream &_save)
{
	_save << "player" << " "
		<< "a" << " "
		<< (unsigned int)id_ << " "
		<< (unsigned int)mapobject_->id_ << " "
		<< std::endl;
}

uint32_t Player::Input(char _ch)
{
	switch(_ch)
	{
		case 'h': if(mapobject_->Move(Vector2<int16_t>(-1,+0))) return mapobject_->timeobject_->speed_;
		case 'j': if(mapobject_->Move(Vector2<int16_t>(+0,+1))) return mapobject_->timeobject_->speed_;
		case 'k': if(mapobject_->Move(Vector2<int16_t>(+0,-1))) return mapobject_->timeobject_->speed_;
		case 'l': if(mapobject_->Move(Vector2<int16_t>(+1,+0))) return mapobject_->timeobject_->speed_;
		case 'b': if(mapobject_->Move(Vector2<int16_t>(-1,+1))) return mapobject_->timeobject_->speed_;
		case 'n': if(mapobject_->Move(Vector2<int16_t>(+1,+1))) return mapobject_->timeobject_->speed_;
		case 'y': if(mapobject_->Move(Vector2<int16_t>(-1,-1))) return mapobject_->timeobject_->speed_;
		case 'u': if(mapobject_->Move(Vector2<int16_t>(+1,-1))) return mapobject_->timeobject_->speed_;
		
		case 's': game.Save();/* game.Pause();*/ break;
//		case 'L': game.Load();/* game.Pause();*/ break;

		case '.': return mapobject_->timeobject_->speed_;

		case 'p': game.Pause(); return 0;
		case 'q': game.End(); return 0;
		
		default: return 0;
	}
}
