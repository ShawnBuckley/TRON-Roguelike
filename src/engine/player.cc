// TRON-Roguelike Player.cc

#include <stdexcept>

#include <stdio.h>

#include "game.hh"
#include "player.hh"
#include "mapobject.hh"
#include "worldtime.hh"

void Player::LoadControls()//(std::string _filename)
// Player::Player()
{
	// TODO - function pointers
	controls_.insert(std::pair<char, PlayerControl>('q', PlayerControl(&Game::End)));
	controls_.insert(std::pair<char, PlayerControl>('p', PlayerControl(&Game::Pause)));
	// controls_.insert(std::pair<char, PlayerControl>('s', PlayerControl()));
	// controls_.insert(std::pair<char, PlayerControl>('L', PlayerControl()));

	controls_.insert(std::pair<char, PlayerControl>('j', PlayerControl(COMT_MOVEMENT, Vector2<int16_t>(+0,+1))));
	controls_.insert(std::pair<char, PlayerControl>('h', PlayerControl(COMT_MOVEMENT, Vector2<int16_t>(-1,+0))));
	controls_.insert(std::pair<char, PlayerControl>('j', PlayerControl(COMT_MOVEMENT, Vector2<int16_t>(+0,+1))));
	controls_.insert(std::pair<char, PlayerControl>('k', PlayerControl(COMT_MOVEMENT, Vector2<int16_t>(+0,-1))));
	controls_.insert(std::pair<char, PlayerControl>('l', PlayerControl(COMT_MOVEMENT, Vector2<int16_t>(+1,+0))));
	controls_.insert(std::pair<char, PlayerControl>('b', PlayerControl(COMT_MOVEMENT, Vector2<int16_t>(-1,+1))));
	controls_.insert(std::pair<char, PlayerControl>('n', PlayerControl(COMT_MOVEMENT, Vector2<int16_t>(+1,+1))));
	controls_.insert(std::pair<char, PlayerControl>('y', PlayerControl(COMT_MOVEMENT, Vector2<int16_t>(-1,-1))));
	controls_.insert(std::pair<char, PlayerControl>('u', PlayerControl(COMT_MOVEMENT, Vector2<int16_t>(+1,-1))));
}

// uint32_t Player::Input(char _ch)
void Player::Think(uint16_t _remaining_time)
{
	for(char ch : game()->io_->keystrokes_)
	{
		if(Controls(ch))
		{
			game()->io_->keystrokes_.remove(ch);
			break;
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

bool Player::Controls(char _ch)
{
	PlayerControl control;
	try
	{
		control = controls_.at(_ch);
	}
	catch(const std::out_of_range& e)
	{
		printf("oof\n");
		return 1;
	}

	if(!control.game_control_ && !game()->paused_)
	{
		moves_.push_back(ControlObjectMove(control.move_type_, 0, control.vector_));
	}
	else
	{
		printf("game control\n");
		(game()->*control.callback_)();
	}

	return 1;
}