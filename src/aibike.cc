// TRON-Roguelike AiBike.cc

#include <cstdio>

#include "engine/game.hh"
#include "engine/maptile.hh"
#include "engine/map.hh"
#include "engine/mapobject.hh"
#include "engine/tiletype.hh"
#include "engine/rng.hh"

#include "aibike.hh"

AiBike::AiBike() : ai_state_(AI_DEFAULT), ai_skill_(100)
{

}

void AiBike::Serialize(YAML::Emitter& out)
{
	out << YAML::BeginMap;
	out << "type" << "AiBike";
	out << "id" << (int)id_;
	if(mapobject_)
		out << "mapobject" << (int)mapobject_->id_;
	else
		out << "mapobject" << "";
	out << "think" << think_;
	out << "ai_state" << (int)ai_state_;
	out << "ai_skill" << (int)ai_skill_;
	out << "tunnel_distance" << (int)tunnel_distance;
	out << "nextmove";
	out << YAML::Flow << YAML::BeginSeq;
	out << next_move_.x << next_move_.y << YAML::EndSeq;
	out << "moves";
	out << YAML::BeginSeq;
	for(ControlObjectMove move : moves_)
		move.Serialize(out);
	out << YAML::EndSeq;
	out << YAML::EndMap;
}

void AiBike::Think()
{
	bool change_direction = 0;

	think_ = 1;

	if(CheckTunnel())
		ai_state_ = AI_TUNNEL;

	switch(ai_state_)
	{
		case AI_DEFAULT: change_direction = Default(); break;
		case AI_TUNNEL: change_direction = Tunnel(); break;
	}

	if(!change_direction)
	{
		moves_.push_back(ControlObjectMove());
	}
}

ControlObjectMove AiBike::Move()
{
	ControlObjectMove move = moves_.front();
	moves_.pop_front();

	if(move.type_ != COMT_NONE)
	{
		mapobject_->Move(move.location_);
	}

	return move;
}

bool AiBike::Default()
{
	Vector2<int16_t> test_coord = mapobject_->location_.maptile_[0][0]->location_ + mapobject_->vector_;

	MapTile* tile = game().map_->Tile(test_coord);

	if(tile == NULL || tile->tiletype_->flags_.solid_ || (!tile->Empty() && CheckMapObjects(tile)))
	{
		return CheckDirection();
	}

	return 0;
}

bool AiBike::Tunnel()
{
	// check the complement
	Vector2<int16_t> test_coord = mapobject_->location_.maptile_[0][0]->location_ + ~mapobject_->vector_;

	if(!CheckTile(game().map_->Tile(test_coord)))
	{
		ChangeDirection(Vector2<int16_t>(mapobject_->vector_.y, mapobject_->vector_.x));
		ai_state_ = AI_DEFAULT;
		return 1;
	}

	test_coord = mapobject_->location_.maptile_[0][0]->location_ - ~mapobject_->vector_;

	if(!CheckTile(game().map_->Tile(test_coord)))
	{
		ChangeDirection(Vector2<int16_t>(-mapobject_->vector_.y, -mapobject_->vector_.x));
		ai_state_ = AI_DEFAULT;
		return 1;
	}

	return Default();
}

bool AiBike::CheckMapObjects(MapTile* _tile)
{
	for(auto mapobject = _tile->mapobject_list_.begin();
		mapobject != _tile->mapobject_list_.end(); ++mapobject)
	{
		if((*mapobject) != NULL && (*mapobject)->flags_.clipping_)
		{
			if((*mapobject)->stats_.mass_ > (&*mapobject_)->stats_.mass_)
				return 1;
		}
	}

	return 0;
}

bool AiBike::CheckTunnel()
{
	Vector2<int16_t> test_coord = mapobject_->location_.maptile_[0][0]->location_ + ~mapobject_->vector_;

	if(CheckTile(game().map_->Tile(test_coord)))
	{
		test_coord = mapobject_->location_.maptile_[0][0]->location_ - ~mapobject_->vector_;

		return (CheckTile(game().map_->Tile(test_coord)));
	}

	return 0;
}

bool AiBike::CheckDirection()
{
	printf("check direction\n");

	Vector2<int16_t> vector(abs(mapobject_->vector_.y), abs(mapobject_->vector_.x));

	for(Vector2<int16_t> check_tile(vector.x, vector.y); ; vector.x ? check_tile.x+=1 : check_tile.y+=1)
	{
		if(CheckTile(game().map_->Tile(mapobject_->location_.maptile_[0][0]->location_ + check_tile)))
		{
			ChangeDirection(-vector);
			return 1;
		}
		if(CheckTile(game().map_->Tile(mapobject_->location_.maptile_[0][0]->location_ - check_tile)))
		{
			ChangeDirection(vector);
			return 1;
		}
	}

	return 0;
}

bool AiBike::CheckTile(MapTile* _tile)
{
	return (_tile == NULL || _tile->tiletype_->flags_.solid_ || _tile->SolidMapObject().size());
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
