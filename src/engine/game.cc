// TRON-Roguelike Game.cc

#include <fstream>

#include "linux.hh"

#include "game.hh"
#include "gl.hh"
#include "sdl.hh"
#include "sector.hh"
#include "io.hh"
#include "player.hh"
#include "worldtime.hh"

Game* game_pointer;

Game::Game()
{
	io_ = std::unique_ptr<IO>(new SDL);
	worldtime_ = std::unique_ptr<WorldTime>(new WorldTime);
	speed_ = 1000;

	run_ = 1;
	paused_ = 0;
	game_pointer = this;
}

void Game::Start()
{
	io_->colors_.push_back(Color(0,0,0));
	io_->colors_.push_back(Color(255,0,0));
	io_->colors_.push_back(Color(0,255,0));
	io_->colors_.push_back(Color(255,255,0));
	io_->colors_.push_back(Color(0,0,255));
	io_->colors_.push_back(Color(255,0,255));
	io_->colors_.push_back(Color(0,0,64));
	io_->colors_.push_back(Color(255,255,255));

	io_->Init();

	io_->SetFPS(20.0f);
	SetRealtime(1);

	map_ = std::unique_ptr<Map>(new Map);

	Sector* sector = new Sector();
	map_->GenerateSector(
		sector,
		AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(0,0),64,64)
	);

	Player* player = AddPlayerMapobject(blue);
	player_->mapobject_->Rez(
		MapLocation<int16_t>(
			AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(8,8), 1, 1)
		),
		Vector2<int16_t>(+0,+0)
	);

	player_->LoadControls();

	Run();
}

void Game::Run()
{
	io_->Map();

	realtime_ = 1;

	while(run_)
	{
		uint32_t input = io_->Input();
		if(paused_)
		{
			player_->Think(0);
			continue;
		}

		if(realtime_)
		{
			worldtime_->WorldTurn(speed_);
		}
		else if(input)
		{
			worldtime_->WorldTurn(input);
		}

		camera_ = player_->mapobject_->location_.maptile_[0][0]->location_;
		io_->Map();
	}
}

void Game::End()
{
	printf("game end!\n");
	run_ = 0;
}

void Game::Pause()
{
	printf("game pause\n");
	paused_ = !paused_;
	SetRealtime(!realtime_);
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
	realtime_ = _realtime;
	
	io_->SetRealtime(_realtime);
}

Game* game()
{
	return game_pointer;
}

void Game::AddControlObject(ControlObject* _controlobject)
{
	if(entity_open_id_.empty())
	{
		entities_.push_back(std::unique_ptr<ControlObject>(_controlobject));
	}
	else
	{
		entities_[entity_open_id_.front()] = std::move(std::unique_ptr<ControlObject>(_controlobject));
		entity_open_id_.pop_front();
	}
}

Player* Game::AddPlayerMapobject(uint8_t _color)
{
	MapObject* mapobject = new MapObject(
		MapObjectStats(),
		MapObjectFlags(1, 1, 1, 1),
		DisplayObject('@', '@', _color)
	);

	ControlObject* controlobject = new Player(mapobject);

	mapobject->timeobject_.mapobject_ = mapobject;
	mapobject->timeobject_.controlobject_ = controlobject;

	AddControlObject(controlobject);

	return (Player*)controlobject;
}