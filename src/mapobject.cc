// TRON-Roguelike MapObject.cc

#include <algorithm>

#include <stdio.h>

#include "color.hh"
#include "main.hh"
#include "mapobject.hh"
#include "map.hh"
#include "maptile.hh"
#include "tiletype.hh"

MapObject::MapObject() : linked_(0)
{
//	printf("Create MapObject %p\n", this);
}

MapObject::MapObject(std::shared_ptr<MapObject> _this, MapObjectFlags _mapobject_flags, std::shared_ptr<DisplayObject> _displayobject,
	std::shared_ptr<TimeObject> _timeobject, std::shared_ptr<MapTile> _maptile, Vector2<int16_t> _vector)
	: linked_(0), flags_(_mapobject_flags), displayobject_(_displayobject), timeobject_(_timeobject)
{
	timeobject_->mapobject_ = _this;

	Rez(std::move(MapLocation<int16_t>(AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(), 1, 1))), _vector);

//	printf("Create MapObject %p\n", this);
}

MapObject::~MapObject()
{
//	printf("Erase MapObject %p\n", this);

	MapUnlink();
}

void MapObject::Save(std::stringstream &_save)
{
	_save << "mapobject" << " "
		<< "a" << " "
		<< id_ << " "
		<< linked_ << " "
		<< (unsigned int)location_.id_ << " "
		<< (signed int)vector_.x << " "
		<< (signed int)vector_.y << " "
		<< flags_.rez_ << " "
		<< flags_.clipping_ << " "
		<< flags_.solid_ << " "
		<< flags_.visible_ << " "
		<< timeobject_->id_ << " "
		<< displayobject_->id_ << " "
		<< std::endl;
}

bool MapObject::Rez(MapLocation<int16_t> _location, Vector2<int16_t> _vector)
{
	if(SetLocation(_location))
	{
		flags_.rez_ = 1;
		vector_ = _vector;
		
		if(timeobject_)
			timeobject_->TimeLink();
		
		return 1;
	}

	return 0;
}

void MapObject::Derez()
{
	displayobject_ = std::move(std::shared_ptr<DisplayObject>(new DisplayObject('X','X',displayobject_->color_)));
	flags_ = MapObjectFlags(0, 0, 0, 1);

	if(timeobject_)
		timeobject_->TimeUnlink();
}

void MapObject::MapLink()
{
	linked_ = 1;
	location_.maptile_.clear();
	
	for(int16_t x=0; x<location_.rectangle_.Width(); ++x)
	{	
		std::vector<std::shared_ptr<MapTile> > row;
	
		for(int16_t y=0; y<location_.rectangle_.Height(); ++y)
		{
			std::shared_ptr<MapTile> maptile = game.map_->Tile(location_.rectangle_.Vertex(0) + Vector2<int16_t>(x, y));
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

bool MapObject::SetLocation(MapLocation<int16_t> _location)
{
	MapUnlink();

	location_ = _location;

	MapLink();

	return 1;
}

bool MapObject::Move(Vector2<int16_t> _vector)
{
	MapLocation<int16_t> location = location_;
	location.rectangle_.Origin(location_.rectangle_.Vertex(0) + _vector);
	
	for(int16_t x=0; x<location.rectangle_.Width(); ++x)
	{	for(int16_t y=0; y<location.rectangle_.Height(); ++y)
	{
		Vector2<int16_t> point(location.rectangle_.Vertex(0).x + x, location.rectangle_.Vertex(0).y + y);
	
		if(location.rectangle_.Intersect(point))
			continue;
			
		if(game.map_->Tile(point) != NULL)
		{
			if(location.maptile_[x][y]->tiletype_->tiletype_flags_.solid_)
				return 0;

			if(location.maptile_[x][y]->AnySolidMapObject())
				return 0;
		}
	}
	}

	return SetLocation(location);
}

bool MapObject::Tick()
{
	if(vector_.x || vector_.y)
	{
		Move(vector_);

		return 1;
	}
	
	return 0;
}
