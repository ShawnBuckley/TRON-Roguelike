// TRON-Roguelike AiBike.cc

#include <cstdio>

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

void AiBike::Think(uint16_t _think_time)
{
	think_ = 1;
	remaining_time_ = _think_time;

	// printf("think time: %i\n", _think_time);

	while(mapobject_->flags_.rez_ && remaining_time_ > mapobject_->timeobject_->speed_)
	{
		// Skill Check
		// if(skill_ < 

		// printf("%p: think - rtime %i : speed %i\n", this, remaining_time_, mapobject_->timeobject_->speed_);

		if(CheckTunnel())
			ai_state_ = AI_TUNNEL;

		switch(ai_state_)
		{
			case AI_DEFAULT: Default(); break;
			case AI_TUNNEL: Tunnel(); break;
		}

		remaining_time_ -= mapobject_->timeobject_->speed_;
	}
}

ControlObjectMove AiBike::Move()
{
	ControlObjectMove move = moves_.front();

	mapobject_->Move(move.location_);
	// mapobject_->vector_ = move.location_;
	moves_.pop_front();

	return move;
}

void AiBike::Default()
{
	Vector2<int16_t> test_coord = mapobject_->location_.maptile_[0][0]->location_ + mapobject_->vector_;

	std::shared_ptr<MapTile> tile = game.map_->Tile(test_coord);

	if(tile == NULL || tile->tiletype_->tiletype_flags_.solid_ || (!tile->Empty() && CheckMapObjects(tile)))
	{
		CheckDirection();
		return;
	}
}

void AiBike::Tunnel()
{
	// check the complement
	Vector2<int16_t> test_coord = mapobject_->location_.maptile_[0][0]->location_ + ~mapobject_->vector_;

	if(!CheckTile(game.map_->Tile(test_coord)))
	{
		ChangeDirection(Vector2<int16_t>(mapobject_->vector_.y, mapobject_->vector_.x));
		ai_state_ = AI_DEFAULT;
		return;
	}

	test_coord = mapobject_->location_.maptile_[0][0]->location_ - ~mapobject_->vector_;

	if(!CheckTile(game.map_->Tile(test_coord)))
	{
		ChangeDirection(Vector2<int16_t>(-mapobject_->vector_.y, -mapobject_->vector_.x));
		ai_state_ = AI_DEFAULT;
		return;
	}

	Default();
}

bool AiBike::CheckMapObjects(std::shared_ptr<MapTile> _tile)
{
	for(auto mapobject = _tile->mapobject_list_.begin();
		mapobject != _tile->mapobject_list_.end(); ++mapobject)
	{
		if(*mapobject == NULL) continue;

		if((*mapobject)->flags_.clipping_)
		{
			if((*mapobject)->CheckBumped(&*mapobject_))
				return 1;
		}
	}

	return 0;
}

bool AiBike::CheckTunnel()
{
	Vector2<int16_t> test_coord = mapobject_->location_.maptile_[0][0]->location_ + ~mapobject_->vector_;

	if(CheckTile(game.map_->Tile(test_coord)))
	{
		test_coord = mapobject_->location_.maptile_[0][0]->location_ - ~mapobject_->vector_;

		return (CheckTile(game.map_->Tile(test_coord)));
	}

	return 0;
}

void AiBike::CheckDirection()
{
	printf("check direction\n");

	Vector2<int16_t> vector(abs(mapobject_->vector_.y), abs(mapobject_->vector_.x));

	for(Vector2<int16_t> check_tile(vector.x, vector.y); ; vector.x ? check_tile.x+=1 : check_tile.y+=1)
	{
		if(CheckTile(game.map_->Tile(mapobject_->location_.maptile_[0][0]->location_ + check_tile)))
		{
			ChangeDirection(-vector);
			break;
		}
		if(CheckTile(game.map_->Tile(mapobject_->location_.maptile_[0][0]->location_ - check_tile)))
		{
			ChangeDirection(vector);
			break;
		}
	}
}

bool AiBike::CheckTile(std::shared_ptr<MapTile> _tile)
{
	return (_tile == NULL || _tile->tiletype_->tiletype_flags_.solid_ || _tile->SolidMapObject().size());
}

void AiBike::ChangeDirection(Vector2<int16_t> _vector)
{
	moves_.push_back(ControlObjectMove(COMT_MOVEMENT, 0, _vector));
	// mapobject_->Move(_vector);
}

void AiBike::AttackEnemy(MapObject *_mapobject)
{
	
}

MapObject* TargetClosestEntity()
{
	
}
