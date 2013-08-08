// TRON-Roguelike Serializerk.hh

#include <yaml-cpp/yaml.h>

#include "controlobject.hh"
#include "game.hh"
#include "gametime.hh"
#include "map.hh"
#include "mapobject.hh"
#include "maptile.hh"
#include "player.hh"
#include "io.hh"
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
	out << YAML::EndMap;

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
}

void Serializer::Serialize(const ControlObjectMove& in)
{
	out << YAML::BeginMap;
	out << "type" << "ControlObjectMove";
	out << "move_type" << (int)in.type_;
	out << "time" << (int)in.time_;
	out << "vector";
	out << YAML::Flow << YAML::BeginSeq;
	out << in.vector_.x << in.vector_.y << YAML::EndSeq;
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
	out << "realtime" << in.realtime_;
	out << "fps" << in.fps_;
	out << "x" << (int)in.x_;
	out << "y" << (int)in.y_;
	out << "camera_mapobject";
	if(in.camera_mapobject_)
		out << in.camera_mapobject_->id_;
	else
		out << -1;	
	out << "camera_location" << YAML::Flow << YAML::BeginSeq;
	out << (int)in.camera_location_.x << (int)in.camera_location_.y << YAML::EndSeq;
	out << "old_color" << (int)in.old_color_;
	// out << "viewport" << YAML::Flow << YAML::BeginSeq;
	// out << viewport_.Vertex(0).x;
	// out << viewport_.Vertex(0).y;
	// out << viewport_.Width();
	// out << viewport_.Height();
	// out << YAML::EndSeq;
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
	out << "rectangle" << YAML::Flow << YAML::BeginSeq;
	out << (int)in.rectangle_.Vertex(0).x << (int)in.rectangle_.Vertex(0).y;
	out << (int)in.rectangle_.Width() << (int)in.rectangle_.Height();
	out << YAML::EndSeq;
	out << YAML::EndMap;
}

void Serializer::Serialize(const MapLocation& in)
{
	out << YAML::BeginMap;
	out << "rectangle";
	out << YAML::Flow << YAML::BeginSeq;
	out << in.rectangle_.Vertex(0).x;
	out << in.rectangle_.Vertex(0).y;
	out << in.rectangle_.Width();
	out << in.rectangle_.Height();
	out << YAML::EndSeq;
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
	out << "vector" << YAML::Flow << YAML::BeginSeq;
	out << (int)in.vector_.x << (int)in.vector_.y << YAML::EndSeq;
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
	out << "timeobject"; Serialize(in.timeobject_);
	out << "location"; Serialize(in.location_);
	out << "vector";
	out << YAML::Flow; out << YAML::BeginSeq;
	out << (int)in.vector_.x << (int)in.vector_.y << YAML::EndSeq;
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
	out << "vector" << YAML::Flow << YAML::BeginSeq;
	out << (int)in.location_.x << (int)in.location_.y << YAML::EndSeq;
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
	out << "rectangle" << YAML::Flow << YAML::BeginSeq;
	out << (int)in.rectangle_.Vertex(0).x << (int)in.rectangle_.Vertex(0).y;
	out << (int)in.rectangle_.Width() << (int)in.rectangle_.Height();
	out << YAML::EndSeq;
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