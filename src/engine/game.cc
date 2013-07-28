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

	io_->camera_mapobject_ = player_->mapobject_;

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

		// camera_ = player_->mapobject_->location_.maptile_[0][0]->location_;
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
//	serialize:
//	game
//		rng
//		game/worldtime
//		map
//			sectors
//				mapobjects
//				items
//		control objects
//			mapobjects
//				extras (lightwalls, etc)
//				inventories
//				

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

DisplayObject* Game::AddDisplayObject(const DisplayObject _displayobject)
{
	DisplayObject* displayobject;

	for(auto it = displayobjects_.begin(); it != displayobjects_.end(); ++it)
	{
		displayobject = (*it).get();

		if(displayobject == NULL)
			continue;

		if((*displayobject == _displayobject))
			return displayobject;
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

void Game::AddMapobject(MapObject* _mapobject)
{
	if(mapobject_open_id_.empty())
	{
		_mapobject->id_ = entities_.size();
		mapobjects_.push_back(std::unique_ptr<MapObject>(_mapobject));
	}
	else
	{
		uint16_t id = mapobject_open_id_.front();

		_mapobject->id_ = id;
		mapobjects_[id] = std::move(std::unique_ptr<MapObject>(_mapobject));
		mapobject_open_id_.pop_front();
	}	
}

void Game::AddControlObject(ControlObject* _controlobject)
{
	if(entity_open_id_.empty())
	{
		_controlobject->id_ = entities_.size();
		entities_.push_back(std::unique_ptr<ControlObject>(_controlobject));
	}
	else
	{
		uint16_t id = entity_open_id_.front();

		_controlobject->id_ = id;
		entities_[id] = std::move(std::unique_ptr<ControlObject>(_controlobject));
		entity_open_id_.pop_front();
	}
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
	AddMapobject(mapobject);

	return (Player*)controlobject;
}