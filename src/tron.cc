// TRON-Roguelike Game.cc

#include <fstream>

#include "engine/linux.hh"

#include "engine/worldtime.hh"
#include "engine/game.hh"
#include "engine/gl.hh"
#include "engine/sdl.hh"
#include "engine/color.hh"

#include "aibike.hh"
#include "bike.hh"
#include "lightgrid.hh"
#include "entitymanager.hh"
#include "tron.hh"

void TRON::Start()
{
	printf("TRON start\n");

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

	Vector2<int16_t> grid_center = lightgrid->rectangle_.Center();

	// printf("viewport (%i %i) %i %i\n", io_->viewport_.Vertex(0).x, io_->viewport_.Vertex(0).y io_->viewport_.Width(), io_->viewport_.Height());
	
	for(auto sector = map_->sector_.begin();
		sector != map_->sector_.end(); ++sector)
	{
		printf("%p (%i %i) %i %i\n", (*sector).get(), (*sector)->rectangle_.Vertex(0).x, (*sector)->rectangle_.Vertex(0).y, (*sector)->rectangle_.Width(), (*sector)->rectangle_.Height());
	}
/*
	player_ = entity_manager_.AddPlayerMapobject(blue);
	player_->mapobject_->Rez(
		MapLocation<int16_t>(
			AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(grid_center.x+1, grid_center.y+1), 1, 1)
		)
	);
/*/
	player_ = EntityManager::AddPlayerBike(blue);
	player_->mapobject_->Rez(
		MapLocation<int16_t>(
			AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(grid_center.x+1, grid_center.y+1), 1, 1)
		),
		Vector2<int16_t>(+0,+0)
	);

	std::shared_ptr<AiBike> red_bike = EntityManager::AddAiBike(red);
	red_bike->mapobject_->Rez(
		MapLocation<int16_t>(
			AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(grid_center.x-1, grid_center.y-1), 1, 1)
		),
		Vector2<int16_t>(-1,+0)
	);

	std::shared_ptr<AiBike> yellow_bike = EntityManager::AddAiBike(yellow);
	yellow_bike->mapobject_->Rez(
		MapLocation<int16_t>(
			AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(grid_center.x+1, grid_center.y-1), 1, 1)
		),
		Vector2<int16_t>(+1,+0)
	);

	std::shared_ptr<AiBike> green_bike = EntityManager::AddAiBike(green);
	green_bike->mapobject_->Rez(
		MapLocation<int16_t>(
			AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(grid_center.x-1, grid_center.y+1), 1, 1)
		),
		Vector2<int16_t>(-1,+0)
	);
//*/
	Run();
}