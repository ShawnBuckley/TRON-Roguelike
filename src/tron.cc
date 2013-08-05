// TRON-Roguelike Game.cc

#include <fstream>

#include <yaml-cpp/yaml.h>

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

TRON::TRON(const YAML::Node& in)
{
	const YAML::Node& game = in["TRON"];
	const YAML::Node& io = in["IO"];
	const YAML::Node& gametime = in["Time"];
	const YAML::Node& displayobjects = in["DisplayObjects"];
	const YAML::Node& tiletypes = in["TileTypes"];
	const YAML::Node& mapobjects = in["MapObjects"];
	const YAML::Node& controlobjects = in["ControlObjects"];
	const YAML::Node& map = in["Map"];
	const YAML::Node& sectors = in["Sectors"];

	version_ = game["version"].as<std::string>();
	run_ = game["run"].as<bool>();
//	paused_ = game["paused"].as<bool>();
	paused_ = 1;
	realtime_ = game["realtime"].as<bool>();

	io_ = std::unique_ptr<IO>(new SDL(io));
	io_->Init();

	UnserializeGameTime(gametime);
	UnserializeDisplayObjects(displayobjects);
	UnserializeTileTypes(tiletypes);
	UnserializeMapObjects(mapobjects);
	UnserializeControlObjects(controlobjects);
	UnserializeTimeObjects(mapobjects);
	UnserializeMap(map);
	UnserializeSectors(sectors);
	UnserializeMapLoactions(mapobjects);

	players_[0]->LoadControls("player.yml");
	players_[1]->LoadControls("player2.yml");

	printf("READY GO!\n");
	// SaveGame("save2");
	SetRealtime(0);
	Run();
}

void TRON::UnserializeMapObjects(const YAML::Node& in)
{
	printf("TRON unserialize mapobjects\n");

	std::vector<Bike*> bikes;

	for(std::size_t i=0; i<in.size(); i++)
	{
		const YAML::Node& mapobject = in[i];

		if(mapobject["type"].as<std::string>() == "Bike")
		{
			Bike* bike = new Bike(mapobject);
			AddMapObject(bike);
			bikes.push_back(bike);
		}
		else if(mapobject["type"].as<std::string>() == "LightWall")
			AddMapObject(new LightWall(mapobject));
	}

	for(Bike* bike : bikes)
	{
		const YAML::Node& mapobject = in[bike->id_];
		for(std::size_t i=0; i<mapobject["lightwalls"].size(); i++)
		{
			bike->wall_list_.push_back((LightWall*)GetMapObject(mapobject["lightwalls"][i].as<int>()));
		}
	}
}

void TRON::UnserializeControlObjects(const YAML::Node& in)
{
	printf("TRON unserialize controlobjects\n");

	for(std::size_t i=0; i<in.size(); i++)
	{
		const YAML::Node& controlobject = in[i];

		if(controlobject["type"].as<std::string>() == "Player")
		{
			Player* player = new Player(controlobject);
			AddControlObject(player);
			game().AddPlayer(player);
		}
		else if(controlobject["type"].as<std::string>() == "AiBike")
			AddControlObject(new AiBike(controlobject));
	}
}

void TRON::UnserializeTimeObjects(const YAML::Node& in)
{
	printf("TRON unserialize timeobjects\n");

	for(std::size_t i=0; i<in.size(); i++)
	{
		const YAML::Node& mapobject = in[i];

		if(mapobject["type"].as<std::string>() == "Bike")
		{
			MapObject* bike = GetMapObject(mapobject["id"].as<int>());
			bike->timeobject_ = TimeObject(mapobject["timeobject"]);
			bike->timeobject_.TimeLink();
		}
	}
}

void TRON::UnserializeMap(const YAML::Node& in)
{
	map_ = std::unique_ptr<Map>(new Map(in));
}

void TRON::UnserializeSectors(const YAML::Node& in)
{
	for(std::size_t i=0; i<in.size(); i++)
	{
		std::unique_ptr<Sector> sector;

		if(in[i]["type"].as<std::string>() == "Sector")
		{
			sector = std::unique_ptr<Sector>(new Sector(in[i]));
		}
		else if(in[i]["type"].as<std::string>() == "LightGrid")
		{
			sector = std::unique_ptr<Sector>(new LightGrid(in[i]));
		}

		map_->sector_.push_back(std::move(sector));
	}
}

void TRON::Serialize(YAML::Emitter& out)
{
	out << "TRON" << YAML::BeginMap;
	out << "version" << version_;
	out << "run" << run_;
	out << "paused" << paused_;
	out << "realtime" << realtime_;
	out << YAML::EndMap;
}

void TRON::Start()
{
	printf("TRON start\n");

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
		MapLocation(
			AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(grid_center.x+1, grid_center.y+1), 1, 1)
		)
	);
/*/
	Player* player = AddPlayerBike(blue);
	player->mapobject_->Rez(
		MapLocation(
			AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(grid_center.x+1, grid_center.y+1), 1, 1)
		),
		Vector2<int16_t>(+0,+0)
	);

	Player* player2 = AddPlayerBike(red);
	player2->mapobject_->Rez(
		MapLocation(
			AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(grid_center.x-1, grid_center.y-1), 1, 1)
		),
		Vector2<int16_t>(+0,+0)
	);

	// AiBike* red_bike = AddAiBike(red);
	// red_bike->mapobject_->Rez(
	// 	MapLocation(
	// 		AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(grid_center.x-1, grid_center.y-1), 1, 1)
	// 	),
	// 	Vector2<int16_t>(-1,+0)
	// );

	AiBike* yellow_bike = AddAiBike(yellow);
	yellow_bike->mapobject_->Rez(
		MapLocation(
			AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(grid_center.x+1, grid_center.y-1), 1, 1)
		),
		Vector2<int16_t>(+1,+0)
	);

	AiBike* green_bike = AddAiBike(green);
	green_bike->mapobject_->Rez(
		MapLocation(
			AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(grid_center.x-1, grid_center.y+1), 1, 1)
		),
		Vector2<int16_t>(-1,+0)
	);

	player->LoadControls("player.yml");
	player2->LoadControls("player2.yml");

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
	AddMapObject(mapobject);

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
	AddMapObject(bike);

	return aibike;
}
