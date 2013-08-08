// TRON-Roguelike TronSerializerk.hh

#include <yaml-cpp/yaml.h>

#include "engine/maptile.hh"

#include "tronserializer.hh"

#include "aibike.hh"
#include "bike.hh"
#include "lightgrid.hh"
#include "lightwall.hh"


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
	out << "tunnel_distance" << (int)in.tunnel_distance;
	out << "next_move";
	out << YAML::Flow << YAML::BeginSeq;
	out << in.next_move_.x << in.next_move_.y << YAML::EndSeq;
	out << "moves";
	out << YAML::BeginSeq;
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
	out << "timeobject"; Serializer::Serialize(in.timeobject_);
	out <<  "location"; Serializer::Serialize(in.location_);
	out << YAML::Key << "vector";
	out << YAML::Flow << YAML::BeginSeq;
	out << in.vector_.x << in.vector_.y << YAML::EndSeq;
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