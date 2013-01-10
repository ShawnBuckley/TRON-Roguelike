// TRON-Roguelike Bike.cc

#include <cstdio>
#include <utility>

#include "main.hh"

#include "mapobject.hh"
#include "game.hh"
#include "bike.hh"
#include "color.hh"
#include "maptile.hh"
#include "tiletype.hh"
#include "map.hh"

const uint8_t kWallSprite[10] = {' ', 192, 179, 217, 196, ' ', 196, 218, 179, 191};
const char kWallPrint[10] = {' ', '\\', '|', '/', '-', ' ', '-', '/', '|', '\\'};

Bike::Bike(std::shared_ptr<Color> _color)
{
	moved_ = 0;
	change_direction_ = 0;

  	for(int i=0; i<10; i++)
		wall_displayobject_[i] = std::move(std::shared_ptr<DisplayObject>(new DisplayObject(kWallPrint[i], kWallSprite[i], _color)));
}

Bike::~Bike() {}

void Bike::Save(std::stringstream &_save)
{
	_save << "bike" << " "
		<< "a" << " "
		<< (unsigned int)id_ << " "
		<< moved_ << " "
		<< change_direction_ << " "
		<< bike_flags_.drop_walls_ << " "
		<< linked_ << " "
		<< (unsigned int)maptile_->id_ << " "
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

void Bike::Derez()
{
	if(flags_.rez_)
	{
		vector_ = Coord2<int8_t>(+0, +0);
		flags_.rez_ = 0;

		MapUnlink();

		flags_ = MapObjectFlags(0, 0, 0, 1);

		displayobject_ = std::move(std::shared_ptr<DisplayObject>(new DisplayObject('X', 'X', displayobject_->color_)));

		MapLink();
	}
}

void Bike::RemoveWall()
{
	if(wall_list_.size())
		wall_list_.erase(wall_list_.begin());
	else
		timeobject_->TimeUnlink();
}

bool Bike::Move(Coord2<int8_t> _vector)
{
	if(!flags_.rez_ || _vector == -vector_ || (_vector.x && _vector.y) || moved_)
		return 0;

	Coord2<int8_t> vector = vector_ + _vector;

	// reverse vector in order to get correct corner DisplayObject
	if(vector_.y) vector = -vector;

	change_direction_ = vector.Direction();

	vector_ = _vector;
	moved_ = 1;
	
	return 1;
}

bool Bike::Tick()
{
	if(flags_.rez_)
	{
		Coord2<uint8_t> test_coord;

		test_coord.y = maptile_->location_.y + vector_.y;
		test_coord.x = maptile_->location_.x + vector_.x;

		std::shared_ptr<MapTile> tile = game.map_->Tile(test_coord);

		if(tile != NULL)
		{
			if(tile->tiletype_->tiletype_flags_.solid_)
			{
				Derez();
				return 0;
			}

			MapObject *mapobject = tile->SolidMapObject();

			if(mapobject != NULL)
			{
				if(mapobject->CheckBumped(this))
				{
					Derez();
					return 0;
				}
				else
				{
					mapobject->Derez();
				}
			}

			if(bike_flags_.drop_walls_)
			{
				if(change_direction_)
				{
					wall_list_.push_back(std::shared_ptr<LightWall>(new LightWall(wall_displayobject_[change_direction_], maptile_, this)));
				
					change_direction_ = 0;
				}
				else
				{
					wall_list_.push_back(std::shared_ptr<LightWall>(new LightWall(wall_displayobject_[vector_.Direction()], maptile_, this)));
				}
			}

			MapObject::Move(vector_);
			moved_ = 0;
			timeobject_->time_ -= timeobject_->speed_;
		}
	}
	else
	{
		RemoveWall();
	}

	return 1;
}
