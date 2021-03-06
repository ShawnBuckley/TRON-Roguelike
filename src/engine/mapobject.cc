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
#include "serializer.hh"

///////////////////////////////////////////////////////////////////////////////
// 
// MapObjectStats
//
///////////////////////////////////////////////////////////////////////////////

void MapObjectStats::Serialize(Serializer& out)
{
	out.Serialize(*this);
}

///////////////////////////////////////////////////////////////////////////////
// 
// MapObjectFlags
//
///////////////////////////////////////////////////////////////////////////////

void MapObjectFlags::Serialize(Serializer& out)
{
	out.Serialize(*this);
}

///////////////////////////////////////////////////////////////////////////////
// 
// MapObjectMove
//
///////////////////////////////////////////////////////////////////////////////

void MapObjectMove::Serialize(Serializer& out)
{
	out.Serialize(*this);
}

///////////////////////////////////////////////////////////////////////////////
// 
// MapObject
//
///////////////////////////////////////////////////////////////////////////////

MapObject::~MapObject()
{
	printf("Erase MapObject %p %i\n", this, id_);

	MapUnlink();
}

void MapObject::Serialize(Serializer& out)
{
	out.Serialize(*this);
}

bool MapObject::Rez(MapLocation _location, Vector2<int16_t> _vector)
{
	if(SetLocation(_location))
	{
		flags_.rez_ = 1;
		vector_ = _vector;

		return 1;
	}

	return 0;
}

void MapObject::Derez()
{
	uint8_t color = displayobject_->color_;

	displayobject_ = game().AddDisplayObject(DisplayObject('X', 'X', color));
	flags_ = MapObjectFlags(0, 0, 0, 1);
	if(timeobject_) game().RemoveTimeObject(timeobject_);
}

void MapObject::MapLink()
{
	// printf("%i maplink!\n", id_);
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
	if(!linked_) 
		return;

	// printf("%i mapunlink!\n", id_);

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
