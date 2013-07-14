// TRON-Roguelike Player.cc

#include <stdio.h>

#include "game.hh"
#include "player.hh"
#include "mapobject.hh"
#include "worldtime.hh"


uint32_t Player::Input(char _ch)
{
	if(!GameControls(_ch) && !game()->game_flags_.paused_)
		return PlayerControls(_ch);

	return 0;
}

bool Player::GameControls(char _ch)
{
	switch(_ch)
	{
		case 's': game()->Save();/* game()->Pause();*/ return 1;
//		case 'L': game()->Load();/* game()->Pause();*/ return 1;

		case 'p': game()->Pause(); return 1;
		case 'q': game()->End(); return 1;
		
		default: return 0;
	}
}

uint32_t Player::PlayerControls(char _ch)
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

		case '.': return mapobject_->timeobject_->speed_;
		
		default: return 0;
	}
}