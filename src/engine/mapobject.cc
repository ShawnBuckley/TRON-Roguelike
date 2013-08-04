// TRON-Roguelike MapObject.cc

#include <algorithm>

#include <stdio.h>

#include <yaml-cpp/yaml.h>

#include "game.hh"
#include "io.hh"
#include "mapobject.hh"
#include "map.hh"
#include "maptile.hh"
#include "tiletype.hh"


MapObject::~MapObject()
{
	// printf("Erase MapObject %p %i\n", this, id_);

	MapUnlink();
}

/*	uint16_t id_;
	bool linked_;
	MapLocation location_;
	Vector2<int16_t> vector_;
	std::list<MapObjectMove> moves_;

	MapObjectStats stats_;
	MapObjectFlags flags_;

	TimeObject timeobject_;
	DisplayObject* displayobject_;*/

void MapObjectStats::Serialize(YAML::Emitter& out)
{
	out << YAML::BeginMap;
	out << YAML::Key << "type";
	out << YAML::Value << "MapObjectStats";
	out << YAML::Key << "mass";
	out << YAML::Value << mass_;
	out << YAML::Key << "health";
	out << YAML::Value << health_;
	out << YAML::EndMap;
}

void MapObjectFlags::Serialize(YAML::Emitter& out)
{
	out << YAML::BeginMap;
	out << YAML::Key << "type";
	out << YAML::Value << "MapObjectFlags";
	out << YAML::Key << "rez";
	out << YAML::Value << rez_;
	out << YAML::Key << "clipping";
	out << YAML::Value << clipping_;
	out << YAML::Key << "solid";
	out << YAML::Value << solid_;
	out << YAML::Key << "visible";
	out << YAML::Value << visible_;
	out << YAML::EndMap;
}

void MapObjectMove::Serialize(YAML::Emitter& out)
{
	out << YAML::BeginMap;
	out << "type" << "MapObjectMove";
	out << "time" << (int)time_;
	out << YAML::Key << "vector";
	out << YAML::Flow;
	out << YAML::Value << YAML::BeginSeq << (int)vector_.x << (int)vector_.y << YAML::EndSeq;
	out << YAML::EndMap;
}

void MapObject::Serialize(YAML::Emitter& out)
{
	out << YAML::BeginMap;
	out << YAML::Key << "type";
	out << YAML::Value << "MapObject";
	out << YAML::Key << "id";
	out << YAML::Value << id_;
	out << YAML::Key << "linked";
	out << YAML::Value << linked_;
	out << YAML::Key << "displayobject";
	out << YAML::Value << (int)displayobject_->id_;
	out << YAML::Key << "stats";
	stats_.Serialize(out);
	out << YAML::Key << "flags";
	flags_.Serialize(out);
	out << YAML::Key << "location";
	location_.Serialize(out);
	out << YAML::Key << "vector";
	out << YAML::Flow;
	out << YAML::Value << YAML::BeginSeq << (int)vector_.x << (int)vector_.y << YAML::EndSeq;
	out << "moves";
	out << YAML::BeginSeq;
	for(MapObjectMove move : moves_)
		move.Serialize(out);
	out << YAML::EndSeq;
	out << YAML::EndMap;
}

bool MapObject::Rez(MapLocation _location, Vector2<int16_t> _vector)
{
	if(SetLocation(_location))
	{
		flags_.rez_ = 1;
		vector_ = _vector;

		if(timeobject_.speed_ > 0)
			timeobject_.TimeLink();
		
		return 1;
	}

	return 0;
}

void MapObject::Derez()
{
	uint8_t color = displayobject_->color_;

	displayobject_ = game().AddDisplayObject(DisplayObject('X', 'X', color));
	flags_ = MapObjectFlags(0, 0, 0, 1);
	timeobject_.TimeUnlink();
}

void MapObject::MapLink()
{
	linked_ = 1;
	location_.maptile_.clear();
	
	for(int16_t x=0; x<location_.rectangle_.Width(); ++x)
	{	
		std::vector<MapTile*> row;
	
		for(int16_t y=0; y<location_.rectangle_.Height(); ++y)
		{
			MapTile* maptile = game().map_->Tile(location_.rectangle_.Vertex(0) + Vector2<int16_t>(x, y));
			Vector2<int16_t> pos = location_.rectangle_.Vertex(0) + Vector2<int16_t>(x, y);

			row.push_back(maptile);
			maptile->mapobject_list_.push_front(this);
		}

		location_.maptile_.push_back(row);
	}
}

void MapObject::MapUnlink()
{
	if(!linked_) return;

	linked_ = 0;
	for(int16_t x=0; x<location_.rectangle_.Width(); ++x)
	{	for(int16_t y=0; y<location_.rectangle_.Height(); ++y)
	{
		location_.maptile_[x][y]->mapobject_list_.remove(this);
	}
	}
}

bool MapObject::SetLocation(MapLocation _location)
{
	MapUnlink();

	location_ = _location;

	MapLink();

	return 1;
}

bool MapObject::Move(Vector2<int16_t> _vector)
{
	MapLocation location = location_;
	location.rectangle_.Origin(location_.rectangle_.Vertex(0) + _vector);
	
	for(int16_t x=0; x<location.rectangle_.Width(); ++x)
	{	for(int16_t y=0; y<location.rectangle_.Height(); ++y)
	{
		Vector2<int16_t> point(location.rectangle_.Vertex(0).x + x, location.rectangle_.Vertex(0).y + y);
	
		if(location.rectangle_.Intersect(point))
			continue;
			
		if(game().map_->Tile(point) != NULL)
		{
			if(location.maptile_[x][y]->tiletype_->flags_.solid_)
				return 0;

			if(location.maptile_[x][y]->AnySolidMapObject())
				return 0;
		}
	}
	}

	return SetLocation(location);
}

uint16_t MapObject::Tick()
{
	if(vector_.x || vector_.y)
	{
		Move(vector_);

		return 1;
	}
	
	return 0;
}
