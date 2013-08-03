// TRON-Roguelike Game.cc

#include <fstream>

#include "engine/linux.hh"

#include "engine/worldtime.hh"
#include "engine/game.hh"
#include "engine/gl.hh"
#include "engine/sdl.hh"
#include "engine/io.hh"

#include "aibike.hh"
#include "bike.hh"
#include "lightgrid.hh"
#include "tron.hh"

void TRON::Start()
{
	printf("TRON start\n");

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

	Sector* sector[4];
	
	for(int i=0; i<4; ++i)
	{
		sector[i] = new Sector();
	}

	Sector* lightgrid = new LightGrid();
	map_->GenerateSector(
		lightgrid,
		AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(8,8),64,64)
	);

	// top
	map_->GenerateSector(
		sector[0],
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
	Player* player = AddPlayerBike(blue);
	player->mapobject_->Rez(
		MapLocation<int16_t>(
			AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(grid_center.x+1, grid_center.y+1), 1, 1)
		),
		Vector2<int16_t>(+0,+0)
	);

	Player* player2 = AddPlayerBike(red);
	player2->mapobject_->Rez(
		MapLocation<int16_t>(
			AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(grid_center.x-1, grid_center.y-1), 1, 1)
		),
		Vector2<int16_t>(+0,+0)
	);

	// AiBike* red_bike = AddAiBike(red);
	// red_bike->mapobject_->Rez(
	// 	MapLocation<int16_t>(
	// 		AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(grid_center.x-1, grid_center.y-1), 1, 1)
	// 	),
	// 	Vector2<int16_t>(-1,+0)
	// );

	AiBike* yellow_bike = AddAiBike(yellow);
	yellow_bike->mapobject_->Rez(
		MapLocation<int16_t>(
			AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(grid_center.x+1, grid_center.y-1), 1, 1)
		),
		Vector2<int16_t>(+1,+0)
	);

	AiBike* green_bike = AddAiBike(green);
	green_bike->mapobject_->Rez(
		MapLocation<int16_t>(
			AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(grid_center.x-1, grid_center.y+1), 1, 1)
		),
		Vector2<int16_t>(-1,+0)
	);

	player->LoadControls("player.json");
	player2->LoadControls("player2.json");

	// io_->camera_mapobject_ = player->mapobject_;
	io_->camera_mapobject_ = NULL;
	io_->camera_location_ = grid_center;

	players_.push_back(player);
	players_.push_back(player2);

	printf("run\n");
	Run();
}

Player* TRON::AddPlayerBike(uint8_t _color)
{
	MapObject* mapobject = new Bike(
		MapObjectFlags(1,1,1,1),
		_color,
		TimeObject(1000));

	Player* player = new Player(mapobject);

	mapobject->timeobject_.mapobject_ = mapobject;
	mapobject->timeobject_.controlobject_ = player;

	AddControlObject(player);
	AddMapobject(mapobject);

	return player;
}

AiBike* TRON::AddAiBike(uint8_t _color)
{
	Bike* bike = new Bike(
		MapObjectFlags(1,1,1,1),
		_color,
		TimeObject(1000));

	AiBike* aibike = new AiBike(bike);

	bike->timeobject_.mapobject_ = bike;
	bike->timeobject_.controlobject_ = aibike;

	AddControlObject(aibike);
	AddMapobject(bike);

	return aibike;
}
