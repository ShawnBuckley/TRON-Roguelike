// TRONLIKE AiBike.cc

#include <cstdio>

#include "coord2.hh"
#include "main.hh"
#include "aibike.hh"
#include "maptile.hh"
#include "map.hh"
#include "mapobject.hh"
#include "tiletype.hh"
#include "rng.hh"

AiBike::AiBike() : ai_state_(AI_DEFAULT), ai_skill_(100)
{

}

AiBike::AiBike(std::shared_ptr<AiBike> _this, std::shared_ptr<Bike> _bike)
	: ai_state_(AI_DEFAULT), ai_skill_(100)
{
	_bike->timeobject_->controlobject_ = _this;
}

void AiBike::Save(std::stringstream &_save)
{
	_save << "aibike" << " "
		<< "a" << " "
		<< (unsigned int)id_ << " "
		<< (unsigned int)ai_state_ << " "
		<< (unsigned int)ai_skill_ << " "
		<< (unsigned int)mapobject_->id_ << " "
		<< std::endl;
}

void AiBike::Think()
{
//	Skill Check

	if(!mapobject_->flags_.rez_)
		return;
		
	if(CheckTunnel())
		ai_state_ = AI_TUNNEL;

	switch(ai_state_)
	{
		case AI_DEFAULT: Default(); break;
		case AI_TUNNEL: Tunnel(); break;
	}
}

void AiBike::Default()
{
	Coord2<uint8_t> test_coord;
	test_coord.x = mapobject_->maptile_->location_.x + mapobject_->vector_.x;
	test_coord.y = mapobject_->maptile_->location_.y + mapobject_->vector_.y;

	std::shared_ptr<MapTile> tile = game.map_->Tile(test_coord);

	if(tile == NULL || tile->tiletype_->tiletype_flags_.solid_)
	{
		CheckDirection();
		return;
	}

	if(!tile->Empty() && CheckMapObjects(tile))
	{
		CheckDirection();
		return;
	}
}

void AiBike::Tunnel()
{
	Coord2<uint8_t> test_coord;
	test_coord.x = mapobject_->maptile_->location_.x + mapobject_->vector_.y;
	test_coord.y = mapobject_->maptile_->location_.y + mapobject_->vector_.x;

	if(!CheckTile(game.map_->Tile(test_coord)))
	{
		ChangeDirection(Coord2<int8_t>(mapobject_->vector_.y, mapobject_->vector_.x));
		ai_state_ = AI_DEFAULT;
		return;
	}

	test_coord.x = mapobject_->maptile_->location_.x - mapobject_->vector_.y;
	test_coord.y = mapobject_->maptile_->location_.y - mapobject_->vector_.x;

	if(!CheckTile(game.map_->Tile(test_coord)))
	{
		ChangeDirection(Coord2<int8_t>(-mapobject_->vector_.y, -mapobject_->vector_.x));
		ai_state_ = AI_DEFAULT;
		return;
	}

	Default();
}

bool AiBike::CheckMapObjects(std::shared_ptr<MapTile> _tile)
{
	printf("check map objects\n");

	for(std::list<MapObject*>::iterator mapobject = _tile->mapobject_list_.begin();
		mapobject != _tile->mapobject_list_.end(); ++mapobject)
	{
		if(*mapobject == NULL) continue;

		if((*mapobject)->flags_.clipping_)
		{
			printf("check bumped\n");
			if((*mapobject)->CheckBumped(&*mapobject_))
				return 1;
		}
	}
	
	return 0;
}

bool AiBike::CheckTunnel()
{
	Coord2<uint8_t> test_coord;
	test_coord.x = mapobject_->maptile_->location_.x + mapobject_->vector_.y;
	test_coord.y = mapobject_->maptile_->location_.y + mapobject_->vector_.x;

	if(CheckTile(game.map_->Tile(test_coord)))
	{
		test_coord.x = mapobject_->maptile_->location_.x - mapobject_->vector_.y;
		test_coord.y = mapobject_->maptile_->location_.y - mapobject_->vector_.x;

		if(CheckTile(game.map_->Tile(test_coord)))
		{
			return 1;
		}
	}

	return 0;
}

void AiBike::CheckDirection()
{
	Coord2<int8_t> vector;
	vector.y = abs(mapobject_->vector_.x);
	vector.x = abs(mapobject_->vector_.y);

	for(Coord2<uint8_t> check_tile(vector.x, vector.y); ; vector.x ? ++check_tile.x : ++check_tile.y)
	{
		if(CheckTile(game.map_->Tile(mapobject_->maptile_->location_ + check_tile)))
		{
			ChangeDirection(-vector);
			break;
		}
		if(CheckTile(game.map_->Tile(mapobject_->maptile_->location_ - check_tile)))
		{
			ChangeDirection(vector);
			break;
		}
	}
}

bool AiBike::CheckTile(std::shared_ptr<MapTile> _tile)
{
	if(_tile == NULL || _tile->tiletype_->tiletype_flags_.solid_ || _tile->SolidMapObject() != NULL)
		return 1;

	return 0;
}

void AiBike::ChangeDirection(Coord2<int8_t> _vector)
{
	mapobject_->Move(_vector);
}

void AiBike::AttackEnemy(MapObject *_mapobject)
{
	
}

MapObject* TargetClosestEntity()
{
	
}
