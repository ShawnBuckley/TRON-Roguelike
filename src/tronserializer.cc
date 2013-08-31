// TRON-Roguelike TronSerializerk.hh

#include "tron.hh"

#include <yaml-cpp/yaml.h>

#include "engine/maptile.hh"

#include "tronserializer.hh"

#include "aibike.hh"
#include "bike.hh"
#include "lightgrid.hh"
#include "lightwall.hh"
#include "tron.hh"

void TronSerializer::Serialize(const AiBike& in)
{
	out << YAML::BeginMap;
	out << "type" << "AiBike";
	out << "id" << (int)in.id_;
	if(in.mapobject_)
		out << "mapobject" << (int)in.mapobject_->id_;
	else
		out << "mapobject" << -1;
	out << "think" << in.think_;
	out << "ai_state" << (int)in.ai_state_;
	out << "ai_skill" << (int)in.ai_skill_;
	out << "tunnel_distance" << (int)in.tunnel_distance_;
	out << "next_move"; Serializer::Serialize(in.next_move_);
	out << "moves" << YAML::BeginSeq;
	for(ControlObjectMove move : in.moves_)
		Serializer::Serialize(move);
	out << YAML::EndSeq;
	out << YAML::EndMap;
}

void TronSerializer::Serialize(const Bike& in)
{
	out << YAML::BeginMap;
	out << "type" << "Bike";
	// out << YAML::Key << "type";
	// out << YAML::Value << "Bike";
	out << "id" << in.id_;
	out << "linked" << in.linked_;
	out << "moved" << in.moved_;
	out << "drop_walls" << in.drop_walls_;
	out << "change_direction" << (int)in.change_direction_;
	out << "time_of_death" << in.time_of_death_;
	out << "displayobject" << (int)in.displayobject_->id_;
	out << "bike_displayobjects" << YAML::Flow << YAML::BeginSeq;
	for(int i=0; i<10; i++)
	{
		out << in.bike_displayobject_[i]->id_;
	}
	out << YAML::EndSeq;
	out << "wall_displayobjects" << YAML::Flow << YAML::BeginSeq;
	for(int i=0; i<10; i++)
	{
		out << in.wall_displayobject_[i]->id_;
	}
	out << YAML::EndSeq;
	out << "stats"; Serializer::Serialize(in.stats_);
	out << "flags"; Serializer::Serialize(in.flags_);
	out << "timeobject"; 
	if(in.timeobject_)
		out << in.timeobject_->id_;
	else
		out << -1; 
	out << "location"; Serializer::Serialize(in.location_);
	out << "vector"; Serializer::Serialize(in.vector_);
	out << "lightwalls";
	out << YAML::Flow << YAML::BeginSeq;
	for(LightWall* wall : in.wall_list_)
		out << (int)wall->id_;
	out << YAML::EndSeq;
	out << "moves";
	out << YAML::Flow << YAML::BeginSeq;
	for(MapObjectMove move : in.moves_)
		Serializer::Serialize(move);
	out << YAML::EndSeq;
	out << YAML::EndMap;
}

void TronSerializer::Serialize(const LightGrid& in)
{
	out << YAML::BeginMap;
	out << "type" << "LightGrid";
	out << "rectangle"; Serializer::Serialize(in.rectangle_);
	out << "tiles" << YAML::BeginSeq;
	std::size_t x_limit = in.tile_.size();
	for(std::size_t x=0; x<x_limit; x++)
	{
		out << YAML::BeginSeq;
		std::size_t y_limit = in.tile_[x].size();
		for(std::size_t y=0; y<y_limit; y++)
		{
			Serializer::Serialize(*in.tile_[x][y]);
		}
		out << YAML::EndSeq;
	}
	out << YAML::EndSeq;
	out << YAML::EndMap;
}

void TronSerializer::Serialize(const LightWall& in)
{
	out << YAML::BeginMap;
	out << "type" << "LightWall";
	out << "id" << in.id_;
	out << "linked" << in.linked_;
	out << "displayobject" << (int)in.displayobject_->id_;
	out << "stats"; Serializer::Serialize(in.stats_);
	out << "flags"; Serializer::Serialize(in.flags_);
	out << "location"; Serializer::Serialize(in.location_);
	out << "bike" << in.bike_->id_;
	out << "time_dropped" << in.time_dropped_;
	out << YAML::EndMap;
}

///////////////////////////////////////////////////////////////////////////////
// 
// Unserialize
// 
///////////////////////////////////////////////////////////////////////////////

AiBike* TronSerializer::UnserializeAiBike(const YAML::Node& in)
{
	MapObject* mapobject = NULL;

	if(in["mapobject"].as<int>() > 0)
		mapobject = game().GetMapObject(in["mapobject"].as<int>());

	std::list<ControlObjectMove> moves;

	for(std::size_t i=0; i<in["moves"].size(); i++)
	{
		moves.push_back(Serializer::UnserializeControlObjectMove(in["moves"][i]));
	}

	return new AiBike(
		in["id"].as<int>(),
		in["think"].as<bool>(),
		(AiState)in["ai_state"].as<int>(),
		in["ai_skill"].as<int>(),
		in["tunnel_distance"].as<int>(),
		UnserializeVector2<int16_t>(in["next_move"]),
		mapobject,
		moves);
}

Bike* TronSerializer::UnserializeBike(const YAML::Node& in)
{
	std::list<MapObjectMove> moves;
	std::array<DisplayObject*, 10> bike_displayobject;
	std::array<DisplayObject*, 10> wall_displayobject;

	for(std::size_t i=0; i<in["moves"].size(); i++)
	{
		moves.push_back(Serializer::UnserializeMapObjectMove(in["moves"][i]));
	}

	for(std::size_t i=0; i<in["bike_displayobjects"].size(); i++)
	{
		bike_displayobject[i] = game().GetDisplayObject(in["bike_displayobjects"][i].as<int>());
	}

	for(std::size_t i=0; i<in["wall_displayobjects"].size(); i++)
	{
		wall_displayobject[i] = game().GetDisplayObject(in["wall_displayobjects"][i].as<int>());
	}

	return new Bike(
		in["id"].as<int>(),
		in["linked"].as<bool>(),
		in["moved"].as<bool>(),
		in["drop_walls"].as<bool>(),
		in["change_direction"].as<int>(),
		in["time_of_death"].as<uint64_t>(),
		game().GetDisplayObject(in["displayobject"].as<int>()),
		Serializer::UnserializeMapObjectStats(in["stats"]),
		Serializer::UnserializeMapObjectFlags(in["flags"]),
		Serializer::UnserializeMapLocation(in["location"]),
		Serializer::UnserializeVector2<int16_t>(in["vector"]),
		bike_displayobject,
		wall_displayobject,
		moves);

}

LightWall* TronSerializer::UnserializeLightWall(const YAML::Node& in)
{
	return new LightWall(
		in["id"].as<int>(),
		game().GetDisplayObject(in["displayobject"].as<int>()),
		Serializer::UnserializeMapObjectStats(in["stats"]),
		Serializer::UnserializeMapLocation(in["location"]),
		(Bike*)game().GetMapObject(in["bike"].as<int>()),
		in["time_dropped"].as<int>());
}

///////////////////////////////////////////////////////////////////////////////
// 
// Load / Reassemble
// 
///////////////////////////////////////////////////////////////////////////////

TRON* TronSerializer::UnserializeTRON(const YAML::Node& in)
{
	// return new TRON();
	TRON* tron = new TRON();

	const YAML::Node& game = in["TRON"];
	const YAML::Node& io = in["IO"];
	const YAML::Node& gametime = in["Time"];
	const YAML::Node& displayobjects = in["DisplayObjects"];
	const YAML::Node& tiletypes = in["TileTypes"];
	const YAML::Node& mapobjects = in["MapObjects"];
	const YAML::Node& controlobjects = in["ControlObjects"];
	const YAML::Node& map = in["Map"];
	const YAML::Node& sectors = in["Sectors"];

	tron->version_ = game["version"].as<std::string>();
	tron->run_ = game["run"].as<bool>();
//	tron->paused_ = game["paused"].as<bool>();
	tron->paused_ = 1;
	tron->realtime_ = game["realtime"].as<bool>();

	tron->io_ = std::unique_ptr<IO>(UnserializeIO(io));
	tron->io_->Init();

	LoadGameTime(gametime);
	LoadDisplayObjects(displayobjects);
	LoadTileTypes(tiletypes);
	LoadMapObjects(mapobjects);
	LoadControlObjects(controlobjects);
	Serializer::LoadTimeObjects(mapobjects);
	LoadMap(map);
	LoadSectors(sectors);
	LoadMapLoactions(mapobjects);

	tron->players_[0]->LoadControls("player.yml");
	tron->players_[1]->LoadControls("player2.yml");

	printf("READY GO!\n");
	// SaveGame("save2");
	tron->Run();
}

void TronSerializer::LoadMapObjects(const YAML::Node& in)
{
	printf("TRON load mapobjects\n");

	std::vector<Bike*> bikes;

	for(std::size_t i=0; i<in.size(); i++)
	{
		const YAML::Node& mapobject = in[i];

		if(mapobject["type"].as<std::string>() == "Bike")
		{
			Bike* bike = UnserializeBike(mapobject);
			game().AddMapObject(bike);
			bikes.push_back(bike);
		}
		else if(mapobject["type"].as<std::string>() == "LightWall")
			game().AddMapObject(UnserializeLightWall(mapobject));
	}

	for(Bike* bike : bikes)
	{
		const YAML::Node& mapobject = in[bike->id_];
		for(std::size_t i=0; i<mapobject["lightwalls"].size(); i++)
		{
			bike->wall_list_.push_back((LightWall*)game().GetMapObject(mapobject["lightwalls"][i].as<int>()));
		}
	}
}

void TronSerializer::LoadControlObjects(const YAML::Node& in)
{
	printf("TRON unserialize controlobjects\n");

	for(std::size_t i=0; i<in.size(); i++)
	{
		const YAML::Node& controlobject = in[i];

		if(controlobject["type"].as<std::string>() == "Player")
		{
			Player* player = UnserializePlayer(controlobject);
			game().AddControlObject(player);
			game().AddPlayer(player);
		}
		else if(controlobject["type"].as<std::string>() == "AiBike")
			game().AddControlObject(UnserializeAiBike(controlobject));
	}
}

void TronSerializer::LoadMap(const YAML::Node& in)
{
	game().map_ = std::unique_ptr<Map>(Serializer::UnserializeMap(in));
}

void TronSerializer::LoadSectors(const YAML::Node& in)
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

		game().map_->sector_.push_back(std::move(sector));
	}
}