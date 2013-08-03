// TRON-Roguelike Bike.cc

#include <cstdio>
#include <utility>

#include "engine/mapobject.hh"
#include "engine/game.hh"
#include "engine/io.hh"
#include "engine/maptile.hh"
#include "engine/tiletype.hh"
#include "engine/map.hh"

#include "bike.hh"

const uint8_t kWallSprite[10] = {' ', 192, 179, 217, 196, '.', 196, 218, 179, 191};
const char kWallPrint[10] = {' ', '\\', '|', '/', '-', '.', '-', '/', '|', '\\'};
const uint8_t kBikeSprite[10] = {' ', ' ', 30, ' ', 17, 254, 16, ' ', 31, ' '};
const char kBikePrint[10] = {' ', ' ', 'v', ' ', '<', 'B', '>', ' ', '^', ' '};

Bike::Bike(MapObjectFlags _mapobject_flags,	uint8_t _color, TimeObject _timeobject)
{
	flags_ = _mapobject_flags;
	timeobject_ = _timeobject;

	for(int i=0; i<10; i++)
	{
		bike_displayobject_[i] = game()->AddDisplayObject(DisplayObject(kBikePrint[i],
			kBikeSprite[i], _color));
		wall_displayobject_[i] = game()->AddDisplayObject(DisplayObject(kWallPrint[i],
			kWallSprite[i], _color));
	}
}

Bike::~Bike() {}

bool Bike::Rez(MapLocation<int16_t> _location, Vector2<int16_t> _vector)
{
	uint8_t direction = _vector.Direction();

	displayobject_ = bike_displayobject_[direction];

	MapObject::Rez(_location, _vector);
}

void Bike::Derez()
{
	printf("derez\n");

	if(flags_.rez_)
	{
		vector_ = Vector2<int16_t>(+0, +0);
		flags_.rez_ = 0;

		MapUnlink();

		flags_ = MapObjectFlags(0, 0, 0, 1);
		displayobject_ = game()->AddDisplayObject(DisplayObject('X', 'X', displayobject_->color_));
		time_of_death_ = game()->time_->TickCount();

		MapLink();
	}
}

void Bike::RemoveWall()
{
	if(wall_list_.size())
	{
		uint64_t time = game()->time_->TickCount() - time_of_death_;
	
		while(wall_list_.size() && time == wall_list_.front()->time_dropped_)
		{
			wall_list_.erase(wall_list_.begin());

			time = game()->time_->TickCount() - time_of_death_;
		}
	}
	else
		timeobject_.TimeUnlink();
}

bool Bike::Move(Vector2<int16_t> _vector)
{
	if(!flags_.rez_ || _vector == -vector_ || (_vector.x && _vector.y) || moved_)
		return 0;

	Vector2<int16_t> vector = vector_ + _vector;

	uint8_t direction = _vector.Direction();

	displayobject_ = bike_displayobject_[direction];

	// reverse vector in order to get correct corner DisplayObject
	if(vector_.y)
		vector = -vector;

	change_direction_ = vector.Direction();

	vector_ = _vector;
	moved_ = 1;
	
	return 1;
}

uint16_t Bike::Tick()
{
	if(!flags_.rez_)
	{
		RemoveWall();

		return timeobject_.speed_;
	}

	// if(vector_ > Vector2<int16_t>(0,0))
	if(vector_.x || vector_.y)
	{
		MapLocation<int16_t> location = location_;
		location.rectangle_.Origin(location_.rectangle_.Vertex(0) + vector_);
	
		for(int16_t x=0; x<location.rectangle_.Width(); ++x)
		{	for(int16_t y=0; y<location.rectangle_.Height(); ++y)
		{
			Vector2<int16_t> test_coord(location.rectangle_.Vertex(0).x + x, location.rectangle_.Vertex(0).y + y);

			MapTile* tile = game()->map_->Tile(test_coord);

			if(tile != NULL)
			{
				if(tile->tiletype_->flags_.solid_)
				{
					Derez();
					return 0;
				}

				std::vector<MapObject*> solid_mapobject = tile->SolidMapObject();

				for(uint8_t i=0; i<solid_mapobject.size(); i++)
				{
					if(solid_mapobject[i] != NULL && solid_mapobject[i] != this)
					{
						if(solid_mapobject[i]->stats_.mass_ > stats_.mass_)
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
			}
		}
		}

		if(bike_flags_.drop_walls_ && (vector_.x || vector_.y))
		{
			MapLocation<int16_t> location = location_;
			location.rectangle_.Origin(location.rectangle_.Vertex(0) + vector_);

			Vector2<int16_t> point = location_.rectangle_.Vertex(0);

			for(; point.x<location_.rectangle_.Width()+location_.rectangle_.Vertex(0).x; point.x += 1)
			{	for(; point.y<location_.rectangle_.Height()+location_.rectangle_.Vertex(0).y; point.y +=1)
			{
				if(!location.rectangle_.Intersect(point))
				{
					wall_list_.push_back(
						std::move(std::unique_ptr<LightWall>(new LightWall(
							wall_displayobject_[change_direction_ ? change_direction_ :vector_.Direction()],
							MapLocation<int16_t>(AxisAligned_Rectangle2<int16_t>(point, 1, 1)),
							game()->time_->TickCount(),
							this
						))
					));
				}
			}
			}
	
			change_direction_ = 0;
		}

		MapObject::Move(vector_);
	}

	moved_ = 0;

	return timeobject_.speed_;
}
