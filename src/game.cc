// TRON-Roguelike Game.cc

#include <fstream>

#include "linux.hh"

#include "aibike.hh"
#include "bike.hh"
#include "game.hh"
#include "gl.hh"
#include "sdl.hh"
#include "color.hh"
#include "lightgrid.hh"
#include "worldtime.hh"

Game::Game()
{
	io_ = std::unique_ptr<IO>(new SDL);
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

	map_ = std::unique_ptr<Map>(new Map);

	std::shared_ptr<Sector> sector[4];
	
	for(int i=0; i<4; ++i)
	{
		sector[i] = std::shared_ptr<Sector>(new Sector());
	}

	std::shared_ptr<Sector> lightgrid(new LightGrid());
	map_->GenerateSector(
		lightgrid,
		AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(8,8),64,64)
	);

	// top
	map_->GenerateSector(
		std::shared_ptr<Sector>(new Sector()),
		AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(0,0),80,8)
	);

	// right
	map_->GenerateSector(
		sector[1],
		AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(72,8),8,64)
	);

	// bottom
	map_->GenerateSector(
		sector[2],
		AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(0,72),80,8)
	);

	// left
	map_->GenerateSector(
		sector[3],
		AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(0,8),8,64)
	);

	Vector2<int16_t> grid_center(
		lightgrid->rectangle_.Vertex(0).x()+lightgrid->rectangle_.Width()/2,
		lightgrid->rectangle_.Vertex(0).y()+lightgrid->rectangle_.Height()/2
	);

	printf("viewport (%i %i) %i %i\n", io_->viewport_.Vertex(0).x(), io_->viewport_.Vertex(0).y(), io_->viewport_.Width(), io_->viewport_.Height());
	
	for(std::vector<std::shared_ptr<Sector> >::iterator sector = map_->sector_.begin();
		sector != map_->sector_.end(); ++sector)
	{
		printf("%p (%i %i) %i %i\n", (*sector).get(), (*sector)->rectangle_.Vertex(0).x(), (*sector)->rectangle_.Vertex(0).y(), (*sector)->rectangle_.Width(), (*sector)->rectangle_.Height());
	}
/*
	player_ = entity_manager_.AddPlayerMapobject(blue);
	player_->mapobject_->Rez(
		MapLocation<int16_t>(
			AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(grid_center.x()+1, grid_center.y()+1), 1, 1)
		)
	);
/*/

	player_ = entity_manager_.AddPlayerBike(blue);
	player_->mapobject_->Rez(
		MapLocation<int16_t>(
			AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(grid_center.x()+1, grid_center.y()+1), 1, 1)
		),
		Vector2<int16_t>(+0,+0)
	);
//*
	std::shared_ptr<AiBike> red_bike = entity_manager_.AddAiBike(red);
	red_bike->mapobject_->Rez(
		MapLocation<int16_t>(
			AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(grid_center.x()-1, grid_center.y()-1), 1, 1)
		),
		Vector2<int16_t>(-1,+0)
	);

	std::shared_ptr<AiBike> yellow_bike = entity_manager_.AddAiBike(yellow);
	yellow_bike->mapobject_->Rez(
		MapLocation<int16_t>(
			AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(grid_center.x()+1, grid_center.y()-1), 1, 1)
		),
		Vector2<int16_t>(+1,+0)
	);

	std::shared_ptr<AiBike> green_bike = entity_manager_.AddAiBike(green);
	green_bike->mapobject_->Rez(
		MapLocation<int16_t>(
			AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(grid_center.x()-1, grid_center.y()+1), 1, 1)
		),
		Vector2<int16_t>(-1,+0)
	);
//*/
	Run();
}

void Game::Run()
{
	printf("game run\n");

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
/*	std::ofstream save_file("save", std::ios::trunc);

	for(std::unordered_map<uint32_t, GameObject*>::iterator it = Object::map_.begin(); it != Object::map_.end(); ++it)
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
