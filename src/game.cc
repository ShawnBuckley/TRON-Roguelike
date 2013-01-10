// TRON-Roguelike Game.cc

#include <fstream>

#include "linux.hh"

#include "aibike.hh"
#include "bike.hh"
#include "game.hh"
#include "gl.hh"
#include "sdl.hh"
#include "curses.hh"
#include "color.hh"
#include "lightgrid.hh"
#include "worldtime.hh"

Game::Game()
{
	io_ = std::unique_ptr<IO>(new SDL);
	map_ = std::unique_ptr<Map>(new LightGrid);
	worldtime_ = std::unique_ptr<WorldTime>(new WorldTime);
}

void Game::Start()
{
	kColor.push_back(std::shared_ptr<Color>(new Color(0,0,0)));
	kColor.push_back(std::shared_ptr<Color>(new Color(255,0,0)));
	kColor.push_back(std::shared_ptr<Color>(new Color(0,255,0)));
	kColor.push_back(std::shared_ptr<Color>(new Color(255,255,0)));
	kColor.push_back(std::shared_ptr<Color>(new Color(0,0,255)));
	kColor.push_back(std::shared_ptr<Color>(new Color(255,0,255)));
	kColor.push_back(std::shared_ptr<Color>(new Color(0,0,64)));
	kColor.push_back(std::shared_ptr<Color>(new Color(255,255,255)));

	io_->Init();

	io_->SetFPS(30.0f);
	SetRealtime(1);

	map_->Gen(1, io_->y_, io_->x_-1);

//	entity_manager_.AddPlayerMapobject(blue);
	player_ = entity_manager_.AddPlayerBike(blue);
	player_->mapobject_->Rez(map_->Tile(Coord2<uint8_t>(map_->x_/2+1, map_->y_/2)), Coord2<int8_t>(+1,+0));
	
	std::shared_ptr<AiBike> ai_bike = entity_manager_.AddAiBike(red);
	ai_bike->mapobject_->Rez(map_->Tile(Coord2<uint8_t>(map_->x_/2-1, map_->y_/2)), Coord2<int8_t>(-1,+0));

	Run();
}

void Game::Run()
{
	io_->Map();

	while(game_flags_.run_)
	{
		io_->Input();
		if(game_flags_.paused_) continue;
		if(game_flags_.realtime_) worldtime_->WorldTurn(player_->mapobject_->timeobject_->speed_);
		io_->Map();
	}
}

void Game::End()
{
	game_flags_.run_ = 0;
}

void Game::Pause()
{
	game_flags_.paused_ = !game_flags_.paused_;
	SetRealtime(!game_flags_.realtime_);
}

void Game::Save()
{
	std::ofstream save_file("save", std::ios::trunc);

	for(std::unordered_map<uint32_t, Object*>::iterator it = Object::map_.begin(); it != Object::map_.end(); ++it)
	{
		if(save_file.good())
		{
			std::stringstream save;
			it->second->Save(save);
			save_file << save.str();
		}
		else
			assert(0);
	}
}

void Game::Load()
{
	
}

void Game::SetRealtime(bool _realtime)
{
	game_flags_.realtime_ = _realtime;
	
	io_->SetRealtime(_realtime);
}
