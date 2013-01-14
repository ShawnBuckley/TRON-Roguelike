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

	Rez(_maptile, _vector);

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
		<< (unsigned int)maptile_->id_ << " "
		<< (signed int)vector_.x() << " "
		<< (signed int)vector_.y() << " "
		<< flags_.rez_ << " "
		<< flags_.clipping_ << " "
		<< flags_.solid_ << " "
		<< flags_.visible_ << " "
		<< timeobject_->id_ << " "
		<< displayobject_->id_ << " "
		<< std::endl;
}

bool MapObject::Rez(std::shared_ptr<MapTile> _maptile, Vector2<int16_t> _vector)
{
	if(SetLocation(_maptile))
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
	maptile_->mapobject_list_.push_front(this);
}

void MapObject::MapUnlink()
{
	if(!linked_) return;

	linked_ = 0;
	maptile_->mapobject_list_.remove(this);
}

bool MapObject::SetLocation(std::shared_ptr<MapTile> _maptile)
{
	MapUnlink();

	maptile_ = _maptile;

	MapLink();

	return 1;
}

bool MapObject::Move(Vector2<int16_t> _vector)
{
	std::shared_ptr<MapTile> tile = game.map_->Tile(maptile_->location_ + _vector);
	
	if(tile != NULL)
	{
		if(tile->tiletype_->tiletype_flags_.solid_)
			return 0;

		if(tile->SolidMapObject() != NULL)
			return 0;

		return SetLocation(tile);
	}

	return 0;
}

bool MapObject::Tick()
{
	if(vector_.x() || vector_.y())
	{
		Move(vector_);

		return 1;
	}
	
	return 0;
}
