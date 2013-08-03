// TRON-Roguelike Player.cc

#include <stdexcept>

#include <stdio.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "game.hh"
#include "player.hh"
#include "mapobject.hh"
#include "worldtime.hh"

std::unordered_map<char, PlayerControl> Player::mapped_controls_;

void Player::LoadControls(std::string _filename)
{
	boost::property_tree::ptree pt;
	boost::property_tree::json_parser::read_json(_filename, pt);

	Player::mapped_controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.quit"), PlayerControl(this, &Game::End)));
	Player::mapped_controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.pause"), PlayerControl(this, &Game::Pause)));
	// Player::mapped_controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.save"), PlayerControl()));
	// Player::mapped_controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.load"), PlayerControl()));

	Player::mapped_controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.move_north"), PlayerControl(this, COMT_MOVEMENT, Vector2<int16_t>(+0,-1))));
	Player::mapped_controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.move_west"), PlayerControl(this, COMT_MOVEMENT, Vector2<int16_t>(-1,+0))));
	Player::mapped_controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.move_south"), PlayerControl(this, COMT_MOVEMENT, Vector2<int16_t>(+0,+1))));
	Player::mapped_controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.move_east"), PlayerControl(this, COMT_MOVEMENT, Vector2<int16_t>(+1,+0))));
	Player::mapped_controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.move_southwest"), PlayerControl(this, COMT_MOVEMENT, Vector2<int16_t>(-1,+1))));
	Player::mapped_controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.move_southeast"), PlayerControl(this, COMT_MOVEMENT, Vector2<int16_t>(+1,+1))));
	Player::mapped_controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.move_northwest"), PlayerControl(this, COMT_MOVEMENT, Vector2<int16_t>(-1,-1))));
	Player::mapped_controls_.insert(std::pair<char, PlayerControl>(pt.get<char>("controls.move_northeast"), PlayerControl(this, COMT_MOVEMENT, Vector2<int16_t>(+1,-1))));
}

// uint32_t Player::Input(char _ch)
void Player::Controls()
{
	for(char ch : game()->io_->keystrokes_)
	{
		if(Controls(ch))
		{
			game()->io_->keystrokes_.remove(ch);
			break;
		}
		// else
		// {
		// 	moves_.push_back(ControlObjectMove());
		// }
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
		control = Player::mapped_controls_.at(_ch);
	}
	catch(const std::out_of_range& e)
	{
		printf("oof\n");
		return 1;
	}

	if(control.player_ != this)
	{
		return 0;
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