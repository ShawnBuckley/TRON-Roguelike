// TRON-Roguelike Serializerk.hh

#include <list>

#include <yaml-cpp/yaml.h>

#include "controlobject.hh"
#include "game.hh"
#include "gametime.hh"
#include "map.hh"
#include "mapobject.hh"
#include "maptile.hh"
#include "player.hh"
#include "io.hh"
#include "sdl.hh"
#include "sector.hh"
#include "serializer.hh"
#include "timeobject.hh"
#include "tiletype.hh"
#include "worldtime.hh"

Serializer::Serializer()
{
	out << YAML::BeginMap;
}

void Serializer::Serialize(const Game& in)
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

	out << in.name_ << YAML::BeginMap;
	out << "version" << in.version_;
	out << "run" << in.run_;
	out << "paused" << in.paused_;
	out << "realtime" << in.realtime_;

	Serialize(*in.io_);
	// rng_->Serialize(out);
	in.time_->Serialize(*this);

	out << "DisplayObjects" << YAML::BeginSeq;
	for(auto it = in.displayobjects_.begin(); it != in.displayobjects_.end(); it++)
	{
		Serialize(*(*it));
	}
	out << YAML::EndSeq;

	out << "TileTypes" << YAML::BeginSeq;
	for(auto it = in.tiletypes_.begin(); it != in.tiletypes_.end(); it++)
	{
		Serialize(*(*it));
	}
	out << YAML::EndSeq;

	out << "MapObjects" << YAML::BeginSeq;
	for(auto it = in.mapobjects_.begin(); it != in.mapobjects_.end(); it++)
	{
		(*it)->Serialize(*this);
	}
	out << YAML::EndSeq;

	out << "ControlObjects" << YAML::BeginSeq;
	for(auto it = in.controlobjects_.begin(); it != in.controlobjects_.end(); it++)
	{
		(*it)->Serialize(*this);
	}
	out << YAML::EndSeq;

	out << "Map";
	Serialize(*in.map_);

	out << "Sectors" << YAML::BeginSeq;
	for(auto it = in.map_->sector_.begin(); it != in.map_->sector_.end(); ++it)
	{
		(*it)->Serialize(*this);
	}
	out << YAML::EndSeq;
	
	out << YAML::EndMap;
	out << YAML::EndMap;
}

void Serializer::Serialize(const Vector2<int16_t> in)
{
	out << YAML::Flow << YAML::BeginSeq;
	out << in.x << in.y << YAML::EndSeq;
}

void Serializer::Serialize(const AxisAligned_Rectangle2<int16_t> in)
{
	out << YAML::Flow << YAML::BeginSeq;
	out << (int)in.Vertex(0).x << (int)in.Vertex(0).y;
	out << (int)in.Width() << (int)in.Height();
	out << YAML::EndSeq;
}

void Serializer::Serialize(const ControlObjectMove& in)
{
	out << YAML::BeginMap;
	out << "type" << "ControlObjectMove";
	out << "move_type" << (int)in.type_;
	out << "time" << (int)in.time_;
	out << "vector"; Serialize(in.vector_);
	out << YAML::EndMap;
}

void Serializer::Serialize(const DisplayObject& in)
{
	out << YAML::BeginMap;
	out << "id" << in.id_;
	out << "print" << (int)in.print_;
	out << "sprite" << (int)in.sprite_;
	out << "color" << (int)in.color_;
	out << YAML::EndMap;
}

void Serializer::Serialize(const GameTime& in)
{
	out << "Time";
	out << YAML::BeginMap;
	out << "type" << "GameTime";
	out << "tick" << in.tick_;
	out << YAML::EndMap;
}

void Serializer::Serialize(const IO& in)
{
	out << "IO";
	out << YAML::BeginMap;
	out << "fps" << in.fps_;
	out << "x" << (int)in.x_;
	out << "y" << (int)in.y_;
	out << "camera_mapobject";
	if(in.camera_mapobject_)
		out << in.camera_mapobject_->id_;
	else
		out << -1;	
	out << "camera_location"; Serialize(in.camera_location_);
	out << "old_color" << (int)in.old_color_;
	// out << "viewport"; Serialize(viewport_);
	out << "keystrokes" << YAML::Flow << YAML::BeginSeq;
	for(char key : in.keystrokes_)
		out << key;
	out << YAML::EndSeq;
	out << YAML::EndMap;
}

void Serializer::Serialize(const TimeObject& in)
{
	out << YAML::BeginMap;
	out << "linked" << in.linked_;
	out << "speed" << (int)in.speed_;
	out << "time" << (int)in.time_;
	out << "mapobject";
	if(in.mapobject_ != NULL)
		out << in.mapobject_->id_;
	else
		out << -1;
	out << "controlobject";
	if(in.controlobject_ != NULL)
		out << in.controlobject_->id_;
	else
		out << -1;
	out << YAML::EndMap;
}

void Serializer::Serialize(const Map& in)
{
	out << YAML::BeginMap;
	out << "type" << "Map";
	out << "rectangle"; Serialize(in.rectangle_);
	out << YAML::EndMap;
}

void Serializer::Serialize(const MapLocation& in)
{
	out << YAML::BeginMap;
	out << "rectangle"; Serialize(in.rectangle_);
	out << YAML::EndMap;
}

void Serializer::Serialize(const MapObjectStats& in)
{
	out << YAML::BeginMap;
	out << "mass" << in.mass_;
	out << "health" << in.health_;
	out << YAML::EndMap;
}

void Serializer::Serialize(const MapObjectFlags& in)
{
	out << YAML::BeginMap;
	out << "rez" << in.rez_;
	out << "clipping" << in.clipping_;
	out << "solid" << in.solid_;
	out << "visible" << in.visible_;
	out << YAML::EndMap;
}

void Serializer::Serialize(const MapObjectMove& in)
{
	out << YAML::BeginMap;
	out << "time" << (int)in.time_;
	out << "vector"; Serialize(in.vector_);
	out << YAML::EndMap;
}

void Serializer::Serialize(const MapObject& in)
{
	out << YAML::BeginMap;
	out << "type" << "MapObject";
	out << "id" << in.id_;
	out << "linked" << in.linked_;
	out << "displayobject" << (int)in.displayobject_->id_;
	out << "stats"; Serialize(in.stats_);
	out << "flags"; Serialize(in.flags_);
	out << "timeobject";
	if(in.timeobject_)
		out << in.timeobject_->id_;
	else
		out << -1;
	out << "location"; Serialize(in.location_);
	out << "vector"; Serialize(in.vector_);
	out << "moves";
	out << YAML::BeginSeq;
	for(MapObjectMove move : in.moves_)
		Serialize(move);
	out << YAML::EndSeq;
	out << YAML::EndMap;
}

void Serializer::Serialize(const MapTile& in)
{
	out << YAML::BeginMap;
	out << "vector"; Serialize(in.location_);
	// out << "sector" << sector_->id_; // TODO
	out << "tiletype" << (int)in.tiletype_->id_;
	out << "mapobjects" << YAML::Flow << YAML::BeginSeq;
	for(MapObject* mapobject : in.mapobject_list_)
	{
		out << (int)mapobject->id_;
	}
	out << YAML::EndSeq;
	out << YAML::EndMap;
}

void Serializer::Serialize(const Player& in)
{
	out << YAML::BeginMap;
	out << "type" << "Player";
	out << "id" << (int)in.id_;
	if(in.mapobject_)
		out << "mapobject" << (int)in.mapobject_->id_;
	else
		out << "mapobject" << -1;

	out << "moves";
	out << YAML::BeginSeq;
	for(ControlObjectMove move : in.moves_)
		Serialize(move);
	out << YAML::EndSeq;
	out << YAML::EndMap;
}

void Serializer::Serialize(const TileTypeFlags& in)
{
	out << YAML::BeginMap;
	out << "render" << in.render_;
	out << "solid" << in.solid_;
	out << YAML::EndMap;
}

void Serializer::Serialize(const TileType& in)
{
	out << YAML::BeginMap;
	out << "id" << in.id_;
	out << "flags"; Serialize(in.flags_);
	out << "displayobject" << in.displayobject_->id_;
	out << YAML::EndMap;
}

void Serializer::Serialize(const Sector& in)
{
	out << YAML::BeginMap;
	out << "type" << "Sector";
	out << "rectangle"; Serialize(in.rectangle_);
	out << "tiles" << YAML::BeginSeq;
	std::size_t x_limit = in.tile_.size();
	for(std::size_t x=0; x<x_limit; x++)
	{
		out << YAML::BeginSeq;
		std::size_t y_limit = in.tile_[x].size();
		for(std::size_t y=0; y<y_limit; y++)
		{
			Serialize(*in.tile_[x][y]);
		}
		out << YAML::EndSeq;
	}
	out << YAML::EndSeq;
	out << YAML::EndMap;
}

void Serializer::Serialize(const WorldTime& in)
{
	out << "Time" << YAML::BeginMap;
	out << "type" << "WorldTime";
	out << "tick" << in.tick_;
	out << "year" << (int)in.date_.year();
	out << "month" << (int)in.date_.month();
	out << "day"<< (int)in.date_.day();
	out << "hour" << (int)in.hour_;
	out << "minute" << (int)in.minute_;
	out << "second" << (int)in.second_;
	out << YAML::EndMap;
}

///////////////////////////////////////////////////////////////////////////////
// 
// Unserialize
// 
///////////////////////////////////////////////////////////////////////////////

Game* Serializer::UnserializeGame(const YAML::Node& in)
{
	const YAML::Node& game_data = in["Game"];
	const YAML::Node& io = game_data["IO"];
	const YAML::Node& gametime = game_data["Time"];
	const YAML::Node& displayobjects = game_data["DisplayObjects"];
	const YAML::Node& tiletypes = game_data["TileTypes"];
	const YAML::Node& mapobjects = game_data["MapObjects"];
	const YAML::Node& controlobjects = game_data["ControlObjects"];
	const YAML::Node& map = game_data["Map"];

	Game* game = new Game();

	game->io_ = std::unique_ptr<IO>(UnserializeIO(io));
	game->io_->Init();

	LoadGameTime(gametime);
	LoadDisplayObjects(displayobjects);
	LoadTileTypes(tiletypes);
	LoadMapObjects(mapobjects);
	LoadControlObjects(controlobjects);
	LoadTimeObjects(mapobjects);
	LoadMap(map);
	// sectors
	LoadMapLoactions(mapobjects);

	printf("end serialization\n");
	printf("READY GO!\n");
	game->Run();
}

IO* Serializer::UnserializeIO(const YAML::Node& in)
{
	std::size_t limit = in["keystrokes"].size();
	std::list<char> keystrokes;

	for(std::size_t i=0; i<limit; i++)
	{
		keystrokes.push_back(in["keystrokes"][i].as<char>());
	}

	return new SDL(in["fps"].as<float>(),
		in["x"].as<int>(), in["y"].as<int>(), in["camera_mapobject"].as<int>(),
		Vector2<int16_t>(in["camera_location"][0].as<int>(),
			in["camera_location"][1].as<int>()),
		keystrokes);
}


GameTime* Serializer::UnserializeGameTime(const YAML::Node& in)
{
	return new GameTime(in["tick"].as<uint64_t>());
}

WorldTime* Serializer::UnserializeWorldTime(const YAML::Node& in)
{
	return new WorldTime(in["tick"].as<uint64_t>(), in["year"].as<int>(),
		in["month}"].as<int>(), in["day"].as<int>(),
		in["hour"].as<uint8_t>(), in["minute"].as<uint8_t>(),
		in["second"].as<uint8_t>());
}

DisplayObject Serializer::UnserializeDisplayObject(const YAML::Node& in)
{
	return DisplayObject(in["id"].as<int>(), in["print"].as<int>(),
			in["sprite"].as<int>(), in["color"].as<int>());
}

TileTypeFlags Serializer::UnserializeTileTypeFlags(const YAML::Node& in)
{
	return TileTypeFlags(in["render"].as<bool>(),
			in["solid"].as<bool>());
}

TileType Serializer::UnserializeTileType(const YAML::Node& in)
{
	return TileType(in["id"].as<uint16_t>(),
			game().GetDisplayObject(in["displayobject"].as<int>()),
			UnserializeTileTypeFlags(in["flags"]));
}

MapObjectStats Serializer::UnserializeMapObjectStats(const YAML::Node& in)
{
	return MapObjectStats(in["mass"].as<int>(), in["health"].as<int>());
}

MapObjectFlags Serializer::UnserializeMapObjectFlags(const YAML::Node& in)
{
	return MapObjectFlags(in["rez"].as<bool>(), in["clipping"].as<bool>(),
		in["solid"].as<bool>(), in["visible"].as<bool>());
}

MapObjectMove Serializer::UnserializeMapObjectMove(const YAML::Node& in)
{
	return MapObjectMove(in["time"].as<uint16_t>(),
		UnserializeVector2<int16_t>(in["vector"]));
}

MapLocation Serializer::UnserializeMapLocation(const YAML::Node& in)
{
	return MapLocation(AxisAligned_Rectangle2<int16_t>(
		UnserializeAxisAligned_Rectangle2<int16_t>(
			in["rectangle"])));
}

TimeObject* Serializer::UnserializeTimeObject(const YAML::Node& in)
{
	MapObject* mapobject = NULL;
	ControlObject* controlobject = NULL;

	if(in["mapobject"].as<int>() >= 0)
		mapobject = game().GetMapObject(in["mapobject"].as<int>());

	if(in["controlobject"].as<int>() >= 0)
		controlobject = game().GetControlObject(in["controlobject"].as<int>());

	return new TimeObject(
		in["id"].as<int>(),
		in["linked"].as<bool>(),
		in["speed"].as<int>(),
		in["time"].as<int>(),
		mapobject,
		controlobject);
}

MapObject* Serializer::UnserializeMapObject(const YAML::Node& in)
{
	std::list<MapObjectMove> moves;

	const YAML::Node& in_moves = in["moves"];
	for(std::size_t i=0; i<moves.size(); i++)
	{
		moves.push_back(UnserializeMapObjectMove(in_moves[i]));
	}

	return new MapObject(
		in["id"].as<int>(), in["linked"].as<bool>(),
		game().GetDisplayObject(in["displayobject"].as<int>()),
		UnserializeMapObjectStats(in["stats"]),
		UnserializeMapObjectFlags(in["flags"]),
		UnserializeMapLocation(in["location"]),
		UnserializeVector2<int16_t>(in["vector"]),
		moves);
}

ControlObjectMove Serializer::UnserializeControlObjectMove(const YAML::Node& in)
{
	return ControlObjectMove(
		(ControlObjectMoveType)in["move_type"].as<int>(),
		in["move_type"].as<uint32_t>(),
		UnserializeVector2<int16_t>(in["vector"]));
}

Player* Serializer::UnserializePlayer(const YAML::Node& in)
{
	uint16_t mapobject_id = in["id"].as<int>();
	MapObject* mapobject;
	std::list<ControlObjectMove> moves;

	for(std::size_t i=0; i<in["moves"].size(); i++)
	{
		moves.push_back(UnserializeControlObjectMove(in["moves"][i]));
	}

	if(mapobject_id >= 0)
		mapobject = game().GetMapObject(mapobject_id);
	else
		mapobject = NULL;

	return new Player(in["id"].as<int>(), mapobject, moves);
}

Map* Serializer::UnserializeMap(const YAML::Node& in)
{
	return new Map(UnserializeAxisAligned_Rectangle2<int16_t>(in["rectangle"]));
}

///////////////////////////////////////////////////////////////////////////////
// 
// Load / Reassemble
// 
///////////////////////////////////////////////////////////////////////////////

void Serializer::LoadGameTime(const YAML::Node& in)
{
	printf("load time\n");

	if(in["type"].as<std::string>() == "WorldTime")
	{
		game().time_ = std::unique_ptr<GameTime>(UnserializeWorldTime(in));
	}
	else
	{
		game().time_ = std::unique_ptr<GameTime>(UnserializeGameTime(in));
	}
}



void Serializer::LoadDisplayObjects(const YAML::Node& in)
{
	printf("load displayobjects\n");

	for(std::size_t i=0; i<in.size(); i++)
	{
		const YAML::Node& displayobject = in[i];
		game().AddDisplayObject(UnserializeDisplayObject(in[i]));
	}
}

void Serializer::LoadTileTypes(const YAML::Node& in)
{
	printf("load tiletypes\n");

	for(std::size_t i=0; i<in.size(); i++)
	{
		game().AddTileType(UnserializeTileType(in[i]));
	}
}

void Serializer::LoadMapObjects(const YAML::Node& in)
{
	printf("load mapobjects\n");

	for(std::size_t i=0; i<in.size(); i++)
	{
		game().AddMapObject(UnserializeMapObject(in[i]));
	}
}

void Serializer::LoadControlObjects(const YAML::Node& in)
{
	printf("load controlobjects\n");

	for(std::size_t i=0; i<in.size(); i++)
	{
		const YAML::Node& controlobject = in[i];
		if(controlobject["type"].as<std::string>() == "Player")
		{
			Player* player = UnserializePlayer(controlobject);
			game().AddControlObject(player);
			game().AddPlayer(player);
		}
	}
}

void Serializer::LoadTimeObjects(const YAML::Node& in)
{
	printf("load timeobjects\n");

	for(std::size_t i=0; i<in.size(); i++)
	{
		TimeObject* timeobject = UnserializeTimeObject(in[i]);
		game().AddTimeObject(timeobject);

		if(timeobject->mapobject_)
			timeobject->mapobject_->timeobject_ = timeobject;
	}
}

void Serializer::LoadMap(const YAML::Node& in)
{
	printf("load map\n");

	game().map_ = std::unique_ptr<Map>(UnserializeMap(in));
}

void Serializer::LoadSectors(const YAML::Node& in)
{
	for(std::size_t i=0; i<in.size(); i++)
	{
		std::unique_ptr<Sector> sector;

		if(in[i]["type"].as<std::string>() == "Sector")
		{
			sector = std::unique_ptr<Sector>(new Sector(in[i]));
		}

		game().map_->sector_.push_back(std::move(sector));
	}
}

void Serializer::LoadMapLoactions(const YAML::Node& in)
{
	for(std::size_t i=0; i < game().mapobjects_.size(); ++i)
	{
		game().mapobjects_[i]->location_.Connect();
		// (*it)->location_.Connect();
	}
}