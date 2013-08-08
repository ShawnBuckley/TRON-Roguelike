// TRON-Roguelike Game.cc

#include <fstream>

#include <yaml-cpp/yaml.h>

#include "linux.hh"

#include "game.hh"
#include "gl.hh"
#include "sdl.hh"
#include "sector.hh"
#include "serializer.hh"
#include "io.hh"
#include "player.hh"
#include "worldtime.hh"

Game* game_pointer;

Game& game()
{
	return *game_pointer;
}

Game::Game()
{
	io_ = std::unique_ptr<IO>(new SDL);
	time_ = std::unique_ptr<GameTime>(new WorldTime);

	name_ = std::string("Game"); 
	version_ = std::string("a");
	run_ = 1;
	paused_ = 0;
	game_pointer = this;
}

Game::Game(const YAML::Node& in)
{
// 	const YAML::Node& game = in["Game"];
// 	const YAML::Node& io = in["IO"];
// 	const YAML::Node& gametime = in["Time"];
// 	const YAML::Node& displayobjects = in["DisplayObjects"];
// 	const YAML::Node& tiletypes = in["TileTypes"];
// 	const YAML::Node& mapobjects = in["MapObjects"];
// 	const YAML::Node& controlobjects = in["ControlObjects"];
// 	const YAML::Node& map = in["Map"];

// 	version_ = game["version"].as<std::string>();
// 	run_ = game["run"].as<bool>();
// //	paused_ = game["paused"].as<bool>();
// 	paused_ = 1;
// 	realtime_ = game["realtime"].as<bool>();

// 	io_ = std::unique_ptr<IO>(new SDL(io));
// 	io_->Init();

// 	UnserializeGameTime(gametime);
// 	UnserializeDisplayObjects(displayobjects);
// 	UnserializeTileTypes(tiletypes);
// 	UnserializeMapObjects(mapobjects);
// 	UnserializeControlObjects(controlobjects);
// 	UnserializeTimeObjects(mapobjects);
// 	UnserializeMap(map);
// 	// sectors
// 	UnserializeMapLoactions(mapobjects);

// 	printf("end serialization\n");
// 	printf("READY GO!\n");
// 	Run();
}

void Game::UnserializeGameTime(const YAML::Node& in)
{
	printf("unserialize gametime\n");

	if(in["type"].as<std::string>() == "WorldTime")
		time_ = std::unique_ptr<GameTime>(new WorldTime(in));
	else
		time_ = std::unique_ptr<GameTime>(new GameTime(in));

	// time_->Unserialize(in);
}

void Game::UnserializeDisplayObjects(const YAML::Node& in)
{
	printf("unserialize displayobjects\n");

	for(std::size_t i=0; i<in.size(); i++)
	{
		const YAML::Node& displayobject = in[i];
		AddDisplayObject(DisplayObject(displayobject));
	}
}

void Game::UnserializeTileTypes(const YAML::Node& in)
{
	printf("unserialize tiletypes\n");

	for(std::size_t i=0; i<in.size(); i++)
	{
		const YAML::Node& tiletype = in[i];
		AddTileType(TileType(tiletype));
	}
}

void Game::UnserializeMapObjects(const YAML::Node& in)
{
	printf("unserialize mapobjects\n");

	for(std::size_t i=0; i<in.size(); i++)
	{
		const YAML::Node& mapobject = in[i];
		AddMapObject(new MapObject(mapobject));
	}
}

void Game::UnserializeControlObjects(const YAML::Node& in)
{
	printf("unserialize controlobjects\n");

	for(std::size_t i=0; i<in.size(); i++)
	{
		const YAML::Node& controlobject = in[i];
		if(controlobject["type"].as<std::string>() == "Player")
		{
			Player* player = new Player(controlobject);
			AddControlObject(player);
			game().AddPlayer(player);
		}
	}
}

void Game::UnserializeTimeObjects(const YAML::Node& in)
{
	// printf("unserialize timeobjects\n");

	// for(std::size_t i=0; i<in.size(); i++)
	// {
	// 	const YAML::Node& mapobject = in[i];
	// 	AddMapObject(new MapObject(mapobject));
	// }
}

void Game::UnserializeMap(const YAML::Node& in)
{
	printf("unserialize map\n");

	map_ = std::unique_ptr<Map>(new Map(in));
}

void Game::UnserializeMapLoactions(const YAML::Node& in)
{
	for(std::size_t i=0; i < mapobjects_.size(); ++i)
	{
		mapobjects_[i]->location_.Connect();
		// (*it)->location_.Connect();
	}
}

void Game::Start()
{
	version_ = std::string("a");
	io_ = std::unique_ptr<IO>(new SDL);
	time_ = std::unique_ptr<GameTime>(new WorldTime);

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
	player->mapobject_->Rez(
		MapLocation(
			AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(8,8), 1, 1)
		),
		Vector2<int16_t>(+0,+0)
	);

	io_->camera_mapobject_ = player->mapobject_;

	player->LoadControls("player.yml");

	players_.push_back(player);

	Run();
}

void Game::Run()
{
	io_->Map();

	run_ = 1;

	while(run_)
	{
		io_->Input();

		for(Player* player : players_)
		{
			if(player) player->Controls();
		}

		if(paused_) continue;

		time_->Turn();

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
	SaveGame("save");
}

void Game::SaveGame(std::string _name)
{
	std::ofstream save;
	save.open("save");
	printf("save\n");

	Serializer out;
	out.Serialize(*this);

	save 
//	<< "---\n" 
	<< out.YAML().c_str();
//	<< "\n...\n";

	printf("end save\n");
	save.close();
}

void Game::SetRealtime(bool _realtime)
{
	realtime_ = _realtime;
	
	io_->SetRealtime(_realtime);
}

DisplayObject* Game::AddDisplayObject(const DisplayObject _displayobject)
{
	DisplayObject* displayobject;

	for(auto it = displayobjects_.begin(); it != displayobjects_.end(); ++it)
	{
		displayobject = (*it).get();

		if(displayobject == NULL)
			continue;

		if((*displayobject == _displayobject))
		{
			printf("duplicate displayobject\n");
			return displayobject;
		}
	}

	displayobject = new DisplayObject(_displayobject);

	if(displayobject_open_id_.empty())
	{
		displayobject->id_ = displayobjects_.size();
		displayobjects_.push_back(std::move(std::unique_ptr<DisplayObject>(displayobject)));
	}
	else
	{
		uint16_t id = displayobject_open_id_.front();

		displayobject->id_ = id;
		displayobjects_[id] = std::move(std::unique_ptr<DisplayObject>(displayobject));
		displayobject_open_id_.pop_front();
	}

	return displayobject;
}

DisplayObject* Game::GetDisplayObject(const uint16_t _id)
{
	return displayobjects_[_id].get();
}

TileType* Game::AddTileType(const TileType _tiletype)
{
	TileType* tiletype;

	for(auto it = tiletypes_.begin(); it != tiletypes_.end(); ++it)
	{
		tiletype = (*it).get();

		if(tiletype == NULL)
			continue;

		if((*tiletype == _tiletype))
			return tiletype;
	}

	tiletype = new TileType(_tiletype);

	if(tiletype_open_id_.empty())
	{
		tiletype->id_ = tiletypes_.size();
		tiletypes_.push_back(std::unique_ptr<TileType>(tiletype));
	}
	else
	{
		uint16_t id = tiletype_open_id_.front();

		tiletype->id_ = id;
		tiletypes_[id] = std::move(std::unique_ptr<TileType>(tiletype));
		tiletype_open_id_.pop_front();
	}

	return tiletype;
}

TileType* Game::GetTileType(uint16_t _id)
{
	return tiletypes_[_id].get();
}

uint16_t Game::AddMapObject(MapObject* _mapobject)
{
	uint16_t id;
	uint16_t old_id = _mapobject->id_;

	if(mapobject_open_id_.empty())
	{
		id = mapobjects_.size();
		_mapobject->id_ = id;
		mapobjects_.push_back(std::move(std::unique_ptr<MapObject>(_mapobject)));
	}
	else
	{
		uint16_t id = mapobject_open_id_.front();

		_mapobject->id_ = id;
		mapobjects_[id] = std::move(std::unique_ptr<MapObject>(_mapobject));
		mapobject_open_id_.pop_front();
	}

	return id;
}

MapObject* Game::GetMapObject(uint16_t _id)
{
	try
	{
		return mapobjects_[_id].get();
	}
	catch(std::out_of_range e)
	{
		printf("out of range!\n");
	}

	return NULL;
}

uint16_t Game::AddControlObject(ControlObject* _controlobject)
{
	uint16_t id = controlobject_open_id_.front();

	if(controlobject_open_id_.empty())
	{
		id = controlobjects_.size();
		_controlobject->id_ = id;
		controlobjects_.push_back(std::unique_ptr<ControlObject>(_controlobject));
	}
	else
	{
		id = controlobject_open_id_.front();

		_controlobject->id_ = id;
		controlobjects_[id] = std::move(std::unique_ptr<ControlObject>(_controlobject));
		controlobject_open_id_.pop_front();
	}

	return id;
}

ControlObject* Game::GetControlObject(uint16_t _id)
{
	return controlobjects_[_id].get();
}

Player* Game::AddPlayerMapobject(uint8_t _color)
{
	DisplayObject* displayobject = AddDisplayObject(DisplayObject('@', '@', _color));
	MapObject* mapobject = new MapObject(
		MapObjectStats(),
		MapObjectFlags(1, 1, 1, 1),
		AddDisplayObject(DisplayObject('@', '@', _color))
	);

	ControlObject* controlobject = new Player(mapobject);

	mapobject->timeobject_.mapobject_ = mapobject;
	mapobject->timeobject_.controlobject_ = controlobject;

	AddControlObject(controlobject);
	AddMapObject(mapobject);

	return (Player*)controlobject;
}

uint16_t Game::AddPlayer(Player* _player)
{
	players_.push_back(_player);
}

void Game::RemoveMapObject(uint16_t _id)
{
	mapobjects_[_id].reset();
	mapobject_open_id_.push_back(_id);
}

void Game::RemoveMapObject(MapObject* _mapobject)
{
	if(_mapobject)
		RemoveMapObject(_mapobject->id_);
}

void Game::RemoveControlObject(uint16_t _id)
{
	controlobjects_[_id].reset();
	controlobject_open_id_.push_back(_id);
}

void Game::RemoveControlObject(ControlObject* _controlobject)
{
	if(_controlobject)
		RemoveControlObject(_controlobject->id_);
}