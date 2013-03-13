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

const int16_t kWallSprite[10] = {' ', 192, 179, 217, 196, '.', 196, 218, 179, 191};
const char kWallPrint[10] = {' ', '\\', '|', '/', '-', '.', '-', '/', '|', '\\'};

Bike::Bike(std::shared_ptr<Color> _color)
{
	moved_ = 0;
	change_direction_ = 0;

  	for(uint8_t i=0; i<10; i++)
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
		<< (unsigned int)location_.id_ << " "
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

void Bike::Derez()
{
	if(flags_.rez_)
	{
		vector_ = Vector2<int16_t>(+0, +0);
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

bool Bike::Move(Vector2<int16_t> _vector)
{
	if(!flags_.rez_ || _vector == -vector_ || (_vector.x() && _vector.y()) || moved_)
		return 0;

	Vector2<int16_t> vector = vector_ + _vector;

	// reverse vector in order to get correct corner DisplayObject
	if(vector_.y())
		vector = -vector;

	change_direction_ = vector.Direction();

	vector_ = _vector;
	moved_ = 1;
	
	return 1;
}

bool Bike::Tick()
{
	if(flags_.rez_)
	{
		Vector2<int16_t> test_coord = location_.maptile_[0][0]->location_ + vector_;

		std::shared_ptr<MapTile> tile = game.map_->Tile(test_coord);

		if(tile != NULL)
		{
			if(tile->tiletype_->tiletype_flags_.solid_)
			{
				Derez();
				return 0;
			}

			std::vector<MapObject*> solid_mapobject = tile->SolidMapObject();

			for(uint8_t i=0; i<solid_mapobject.size(); i++)
			{
				if(solid_mapobject[i] != NULL && solid_mapobject[i] != this)
				{
					if(solid_mapobject[i]->CheckBumped(this))
					{
						Derez();
						return 0;
					}
					else
					{
						solid_mapobject[i]->Derez();
					}
				}
			}

			if(bike_flags_.drop_walls_ && (vector_.x() || vector_.y()))
			{
				if(change_direction_)
				{
					wall_list_.push_back(std::shared_ptr<LightWall>(
						new LightWall(
							wall_displayobject_[change_direction_],
							location_,
							this
						)
					));
				
					change_direction_ = 0;
				}
				else
				{
					wall_list_.push_back(std::shared_ptr<LightWall>(
						new LightWall(
							wall_displayobject_[vector_.Direction()],
							location_,
							this
						)
					));
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
