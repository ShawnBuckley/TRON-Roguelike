// TRON-Roguelike Player.cc

#include <stdexcept>

#include <stdio.h>

#include <yaml-cpp/yaml.h>

#include "game.hh"
#include "player.hh"
#include "mapobject.hh"
#include "worldtime.hh"
#include "serializer.hh"

std::unordered_map<char, PlayerControl> Player::mapped_controls_;

///////////////////////////////////////////////////////////////////////////////
// 
// Player
// 
///////////////////////////////////////////////////////////////////////////////

void Player::Serialize(Serializer& out)
{
	out.Serialize(*this);
}

void Player::LoadControls(std::string _filename)
{
	YAML::Node node = YAML::LoadFile(_filename);

	// for(YAML::const_iterator it=node.begin();it!=node.end();++it)
	// 	std::cout << it->as<char>() << "\n";

	Player::mapped_controls_.insert(std::pair<char, PlayerControl>(node["quit"].as<char>(), PlayerControl(this, &Game::End)));
	Player::mapped_controls_.insert(std::pair<char, PlayerControl>(node["pause"].as<char>(), PlayerControl(this, &Game::Pause)));
	Player::mapped_controls_.insert(std::pair<char, PlayerControl>(node["save"].as<char>(), PlayerControl(this, &Game::Save)));
	// Player::mapped_controls_.insert(std::pair<char, PlayerControl>(node["load"].as<char>(), PlayerControl(this, &Game::Load)));

	Player::mapped_controls_.insert(std::pair<char, PlayerControl>(node["move_north"].as<char>(), PlayerControl(this, COMT_MOVEMENT, Vector2<int16_t>(+0,-1))));
	Player::mapped_controls_.insert(std::pair<char, PlayerControl>(node["move_west"].as<char>(), PlayerControl(this, COMT_MOVEMENT, Vector2<int16_t>(-1,+0))));
	Player::mapped_controls_.insert(std::pair<char, PlayerControl>(node["move_south"].as<char>(), PlayerControl(this, COMT_MOVEMENT, Vector2<int16_t>(+0,+1))));
	Player::mapped_controls_.insert(std::pair<char, PlayerControl>(node["move_east"].as<char>(), PlayerControl(this, COMT_MOVEMENT, Vector2<int16_t>(+1,+0))));
	Player::mapped_controls_.insert(std::pair<char, PlayerControl>(node["move_southwest"].as<char>(), PlayerControl(this, COMT_MOVEMENT, Vector2<int16_t>(-1,+1))));
	Player::mapped_controls_.insert(std::pair<char, PlayerControl>(node["move_southeast"].as<char>(), PlayerControl(this, COMT_MOVEMENT, Vector2<int16_t>(+1,+1))));
	Player::mapped_controls_.insert(std::pair<char, PlayerControl>(node["move_northwest"].as<char>(), PlayerControl(this, COMT_MOVEMENT, Vector2<int16_t>(-1,-1))));
	Player::mapped_controls_.insert(std::pair<char, PlayerControl>(node["move_northeast"].as<char>(), PlayerControl(this, COMT_MOVEMENT, Vector2<int16_t>(+1,-1))));
}

void Player::Controls()
{
	printf("player controls\n");
	for(char ch : game().io_->keystrokes_)
	{
		if(Controls(ch))
		{
			return;
		}
	}

	// moves_.push_back(ControlObjectMove());
}

ControlObjectMove Player::Move()
{
	if(moves_.size())
	{
		ControlObjectMove move = moves_.front();

		mapobject_->Move(move.vector_);
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
		game().io_->keystrokes_.remove(_ch);
		return 1;
	}

	if(control.player_ == this)
	{
		printf("player == this\n");
		game().io_->keystrokes_.remove(_ch);

		if(control.game_control_)
		{
			printf("game control\n");
			(game().*control.callback_)();
		}
		else if(!game().paused_)
		{
			printf("else not\n");
			moves_.push_back(ControlObjectMove(control.move_type_, 0, control.vector_));
		}

		return 1;
	}

	return 0;
}