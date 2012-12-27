// Rogulike EngineX Game.cc

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

std::shared_ptr<AiBike> ai_bike;

Game::Game()
{
	io_ = std::unique_ptr<IO>(new SDL);
	map_ = std::unique_ptr<Map>(new LightGrid);
	worldtime_ = std::unique_ptr<WorldTime>(new WorldTime);
}

void Game::Start()
{
	io_->Init();

	io_->SetFPS(30.0f);
	SetRealtime(1);

	map_->Gen(1, io_->y_, io_->x_-1);
//	map_->Gen(1,24,24);
/*/
	player_.mapobject_ = std::move(std::shared_ptr<MapObject>(new MapObject));
	player_.mapobject_->timeobject_ = std::move(std::shared_ptr<TimeObject>(new TimeObject(6000));
	player_.mapobject_->displayobject_ = std::move(std::shared_ptr<DisplayObject>(new DisplayObject('@', '@', kBlue)));
	player_.mapobject_->flags_ = MapObjectFlags(1, 1, 1, 1);
	player_.mapobject_->Rez(Coord2<uint8_t>(map_->x_/2+1, map_->y_/2));
	player_.mapobject_->timeobject_->TimeLink();
	player_.mapobject_->timeobject_->mapobject_= player_.mapobject_;
/*/
	player_ = std::move(std::shared_ptr<Player>(new Player));
	player_->mapobject_ = std::move(std::shared_ptr<Bike>(new Bike(kBlue)));
	player_->mapobject_->timeobject_ = std::move(std::shared_ptr<TimeObject>(new TimeObject(1000)));
	player_->mapobject_->displayobject_ = std::move(std::shared_ptr<DisplayObject>(new DisplayObject('@', 254, kBlue)));
	player_->mapobject_->flags_ = MapObjectFlags(1, 1, 1, 1);
	player_->mapobject_->Rez(map_->Tile(Coord2<uint8_t>(map_->x_/2+1, map_->y_/2)), Coord2<int8_t>(+1,+0));
	player_->mapobject_->timeobject_->TimeLink();
	player_->mapobject_->timeobject_->mapobject_= player_->mapobject_;
	player_->mapobject_->timeobject_->controlobject_ = player_;
//*/
	ai_bike = std::move(std::shared_ptr<AiBike>(new AiBike));
	ai_bike->mapobject_ = std::shared_ptr<Bike>(new Bike(kRed));
	ai_bike->mapobject_->timeobject_ = std::move(std::shared_ptr<TimeObject>(new TimeObject(1000)));
	ai_bike->mapobject_->displayobject_ = std::move(std::shared_ptr<DisplayObject>(new DisplayObject('B', 254, kRed)));
	ai_bike->mapobject_->flags_ = MapObjectFlags(1, 1, 1, 1);
	ai_bike->mapobject_->Rez(map_->Tile(Coord2<uint8_t>(map_->x_/2-1, map_->y_/2)), Coord2<int8_t>(-1,+0));
	ai_bike->mapobject_->timeobject_->TimeLink();
	ai_bike->mapobject_->timeobject_->mapobject_= ai_bike->mapobject_;
	ai_bike->mapobject_->timeobject_->controlobject_ = ai_bike;
/*	
//	Init AiBike
	std::shared_ptr<Bike> bike;
	std::shared_ptr<AiBike> ai_bike;
	std::shared_ptr<DisplayObject> ai_bike_displayobject(new DisplayObject('P', 'P', kRed));
	
	bike = std::shared_ptr<MapObject>(new Bike(
		bike,
		MapObjectFlags(1, 1, 1, 1),
//		std::move(std::shared_ptr<DisplayObject>(new DisplayObject('P', 'P', kRed))),
		ai_bike_displayobject,
		std::move(std::shared_ptr<TimeObject>(new TimeObject(1000))),
		Coord2<uint8_t>(map_->x_/2-1, map_->y_/2),
		Coord2<int8_t>(-1,+0)
	));

	ai_bike = std::shared_ptr<AiBike>(new AiBike(
		ai_bike,
		bike
	));
		
	entities_.push_back(std::move(ai_bike));

	std::shared_ptr<MapObject> program;
	program = (new MapObject(
		MapObjectFlags(1, 1, 1, 1),
		std::move(std::shared_ptr<DisplayObject>(new DisplayObject('P', 'P', kGreen))),
		std::move(std::shared_ptr<TimeObject>(new TimeObject(1000))),
		Coord2<uint8_t>(map_->x_/2+9, map_->y_/2-1),
		Coord2<int8_t>(+0,+0)
	));
	
//	entities_.push_back(std::move(program));

//*/
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
