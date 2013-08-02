// TRON-Roguelike Player.cc

#include <stdexcept>

#include <stdio.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "game.hh"
#include "player.hh"
#include "mapobject.hh"
#include "worldtime.hh"

void Player::LoadControls(std::string _filename)
{
	boost::property_tree::ptree pt;
	boost::property_tree::json_parser::read_json(_filename, pt);

	controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.quit"), PlayerControl(&Game::End)));
	controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.pause"), PlayerControl(&Game::Pause)));
	// controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.save"), PlayerControl()));
	// controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.load"), PlayerControl()));

	controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.move_north"), PlayerControl(COMT_MOVEMENT, Vector2<int16_t>(+0,-1))));
	controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.move_west"), PlayerControl(COMT_MOVEMENT, Vector2<int16_t>(-1,+0))));
	controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.move_south"), PlayerControl(COMT_MOVEMENT, Vector2<int16_t>(+0,+1))));
	controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.move_east"), PlayerControl(COMT_MOVEMENT, Vector2<int16_t>(+1,+0))));
	controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.move_southwest"), PlayerControl(COMT_MOVEMENT, Vector2<int16_t>(-1,+1))));
	controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.move_southeast"), PlayerControl(COMT_MOVEMENT, Vector2<int16_t>(+1,+1))));
	controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.move_northwest"), PlayerControl(COMT_MOVEMENT, Vector2<int16_t>(-1,-1))));
	controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.move_northeast"), PlayerControl(COMT_MOVEMENT, Vector2<int16_t>(+1,-1))));
}

// uint32_t Player::Input(char _ch)
void Player::Think()
{
	for(char ch : game()->io_->keystrokes_)
	{
		if(Controls(ch))
		{
			game()->io_->keystrokes_.remove(ch);
			break;
		}
		else
		{
			moves_.push_back(ControlObjectMove());
		}
	}
}

ControlObjectMove Player::Move()
{
	if(moves_.size())
	{
		ControlObjectMove move = moves_.front();

		mapobject_->Move(move.location_);
		// mapobject_->vector_ = move.location_;
		moves_.pop_front();

		return move;
	}

	return ControlObjectMove();
}

bool Player::Controls(char _ch)
{
	PlayerControl control;
	try
	{
		printf("char: %c\n", _ch);
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