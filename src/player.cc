// RLengineX Player.cc

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

bool Player::Input(char _ch)
{
	switch(_ch)
	{
		case 'h': if(mapobject_->Move(Coord2<int8_t>(-1,+0))) { game.worldtime_->WorldTurn(mapobject_->timeobject_->speed_); } return 1;
		case 'j': if(mapobject_->Move(Coord2<int8_t>(+0,+1))) { game.worldtime_->WorldTurn(mapobject_->timeobject_->speed_); } return 1;
		case 'k': if(mapobject_->Move(Coord2<int8_t>(+0,-1))) { game.worldtime_->WorldTurn(mapobject_->timeobject_->speed_); } return 1;
		case 'l': if(mapobject_->Move(Coord2<int8_t>(+1,+0))) { game.worldtime_->WorldTurn(mapobject_->timeobject_->speed_); } return 1;
		case 'b': if(mapobject_->Move(Coord2<int8_t>(-1,+1))) { game.worldtime_->WorldTurn(mapobject_->timeobject_->speed_); } return 1;
		case 'n': if(mapobject_->Move(Coord2<int8_t>(+1,+1))) { game.worldtime_->WorldTurn(mapobject_->timeobject_->speed_); } return 1;
		case 'y': if(mapobject_->Move(Coord2<int8_t>(-1,-1))) { game.worldtime_->WorldTurn(mapobject_->timeobject_->speed_); } return 1;
		case 'u': if(mapobject_->Move(Coord2<int8_t>(+1,-1))) { game.worldtime_->WorldTurn(mapobject_->timeobject_->speed_); } return 1;
		
		case 's': game.Save();/* game.Pause();*/ break;
//		case 'L': game.Load();/* game.Pause();*/ break;
/*
		case 'h': velocity = Coord2<int8_t>(-1,+0); game.worldtime_->WorldTurn(mapobject_->timeobject_->speed_); return 1;
		case 'j': velocity = Coord2<int8_t>(+0,+1); game.worldtime_->WorldTurn(mapobject_->timeobject_->speed_); return 1;
		case 'k': velocity = Coord2<int8_t>(+0,-1); game.worldtime_->WorldTurn(mapobject_->timeobject_->speed_); return 1;
		case 'l': velocity = Coord2<int8_t>(+1,+0); game.worldtime_->WorldTurn(mapobject_->timeobject_->speed_); return 1;
		case 'b': velocity = Coord2<int8_t>(-1,+1); game.worldtime_->WorldTurn(mapobject_->timeobject_->speed_); return 1;
		case 'n': velocity = Coord2<int8_t>(+1,+1); game.worldtime_->WorldTurn(mapobject_->timeobject_->speed_); return 1;
		case 'y': velocity = Coord2<int8_t>(-1,-1); game.worldtime_->WorldTurn(mapobject_->timeobject_->speed_); return 1;
		case 'u': velocity = Coord2<int8_t>(+1,-1); game.worldtime_->WorldTurn(mapobject_->timeobject_->speed_); return 1;
*/
		case '.': game.worldtime_->WorldTurn(mapobject_->timeobject_->speed_); return 1;

		case 'p': game.Pause(); return 0;
		case 'q': game.End(); return 0;
		
		default: return 0;
	}
}
