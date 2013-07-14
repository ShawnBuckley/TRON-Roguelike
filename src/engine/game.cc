// TRON-Roguelike Game.cc

#include <fstream>

#include "linux.hh"

#include "game.hh"
#include "gl.hh"
#include "sdl.hh"
#include "sector.hh"
#include "color.hh"
#include "player.hh"
#include "worldtime.hh"

Game* game_pointer;

Game::Game()
{
	io_ = std::unique_ptr<IO>(new SDL);
	worldtime_ = std::unique_ptr<WorldTime>(new WorldTime);
	speed_ = 1000;

	game_pointer = this;
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

	io_->SetFPS(20.0f);
	SetRealtime(1);

	map_ = std::unique_ptr<Map>(new Map);

	std::shared_ptr<Sector> sector = std::shared_ptr<Sector>(new Sector());
	map_->GenerateSector(
		sector,
		AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(0,0),64,64)
	);

	player_ = std::shared_ptr<Player>(new Player);
	player_->mapobject_ = std::move(std::shared_ptr<MapObject>(new MapObject));
	player_->mapobject_->displayobject_ = std::move(std::shared_ptr<DisplayObject>(new DisplayObject('@', '@', kColor[blue])));
	player_->mapobject_->flags_ = MapObjectFlags(1, 1, 1, 1);
	player_->mapobject_->timeobject_ = std::move(std::shared_ptr<TimeObject>(new TimeObject(6000)));
	player_->mapobject_->Rez(
		MapLocation<int16_t>(
			AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(8,8), 1, 1)
		),
		Vector2<int16_t>(+0,+0)
	);

	Run();
}

void Game::Run()
{
	io_->Map();

	game_flags_.realtime_ = 1;

	while(game_flags_.run_)
	{
		uint32_t input = io_->Input();
		if(game_flags_.paused_)
			continue;
		if(game_flags_.realtime_)
			worldtime_->WorldTurn(speed_);
		else if(input)
			worldtime_->WorldTurn(input);
		camera_ = player_->mapobject_->location_.maptile_[0][0]->location_;
		io_->Map();
	}
	printf("exit run\n");
}

void Game::End()
{
	printf("game end!\n");
	game_flags_.run_ = 0;
}

void Game::Pause()
{
	game_flags_.paused_ = !game_flags_.paused_;
	SetRealtime(!game_flags_.realtime_);
}

void Game::Save()
{
/*	std::ofstream save_file("save", std::ios::trunc);

	for(auto it = Object::map_.begin(); it != Object::map_.end(); ++it)
	{
		if(save_file.good())
		{
			std::stringstream save;
			it->second->Save(save);
			save_file << save.str();
		}
	}*/
}

void Game::Load()
{
//	std::ifstream save_file("save", std::ios::begin);
}

void Game::SetRealtime(bool _realtime)
{
	game_flags_.realtime_ = _realtime;
	
	io_->SetRealtime(_realtime);
}

Game* game()
{
	return game_pointer;
}