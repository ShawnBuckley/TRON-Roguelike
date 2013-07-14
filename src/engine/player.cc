// TRON-Roguelike Player.cc

#include <stdio.h>

#include "game.hh"
#include "player.hh"
#include "mapobject.hh"
#include "worldtime.hh"


// uint32_t Player::Input(char _ch)
void Player::Think(uint16_t _remaining_time)
{
	// check io controls list

	for(char ch : game()->io_->keystrokes_)
	{
		if(!GameControls(ch) && !game()->game_flags_.paused_)
		{
			if(PlayerControls(ch))
			{
				game()->io_->keystrokes_.remove(ch);
				break;
			}
		}
	}
}

ControlObjectMove Player::Move()
{
	ControlObjectMove move = moves_.front();

	mapobject_->Move(move.location_);
	// mapobject_->vector_ = move.location_;
	moves_.pop_front();

	return move;
}

bool Player::GameControls(char _ch)
{
	switch(_ch)
	{
// 		case 's': game()->Save();/* game()->Pause();*/ return 1;
//		case 'L': game()->Load();/* game()->Pause();*/ return 1;

		case 'p': game()->Pause(); return 1;
		case 'q': game()->End(); return 1;
	}

	return 0;
}

bool Player::PlayerControls(char _ch)
{	
	switch(_ch)
	{
		case 'h': moves_.push_back(ControlObjectMove(COMT_MOVEMENT, 0, Vector2<int16_t>(-1,+0))); return 1;
		case 'j': moves_.push_back(ControlObjectMove(COMT_MOVEMENT, 0, Vector2<int16_t>(+0,+1))); return 1;
		case 'k': moves_.push_back(ControlObjectMove(COMT_MOVEMENT, 0, Vector2<int16_t>(+0,-1))); return 1;
		case 'l': moves_.push_back(ControlObjectMove(COMT_MOVEMENT, 0, Vector2<int16_t>(+1,+0))); return 1;
		case 'b': moves_.push_back(ControlObjectMove(COMT_MOVEMENT, 0, Vector2<int16_t>(-1,+1))); return 1;
		case 'n': moves_.push_back(ControlObjectMove(COMT_MOVEMENT, 0, Vector2<int16_t>(+1,+1))); return 1;
		case 'y': moves_.push_back(ControlObjectMove(COMT_MOVEMENT, 0, Vector2<int16_t>(-1,-1))); return 1;
		case 'u': moves_.push_back(ControlObjectMove(COMT_MOVEMENT, 0, Vector2<int16_t>(+1,-1))); return 1;

		case '.': moves_.push_back(ControlObjectMove(COMT_WAIT, 0, Vector2<int16_t>(0,0))); return 1;
	}

	return 0;
}