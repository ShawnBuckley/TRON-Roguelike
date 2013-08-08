// TRON-Roguelike ControlObject.hh

#ifndef TRON_RLENGINEX_CONTROLOBJECT_HH
#define TRON_RLENGINEX_CONTROLOBJECT_HH

#include <cstdlib>
#include <memory>
#include <list>

#include <yaml-cpp/yaml.h>

#include "math/vector2.hh"

class MapObject;
class Serializer;

enum ControlObjectMoveType
{
	COMT_NONE = 0,
	COMT_MOVEMENT = 1,
	COMT_WAIT,
	COMT_ABILITY,
	COMT_EQUIPMENT,
	COMT_ITEM,
};

class ControlObjectMove
{
  public:
  	ControlObjectMove() : type_(COMT_NONE), time_(0) {};
  	ControlObjectMove(ControlObjectMoveType _type, uint16_t _time, Vector2<int16_t> _vector)
		: type_(_type), time_(_time), vector_(_vector) {};
	ControlObjectMove(const YAML::Node& in)
	{
		type_ = (ControlObjectMoveType)in["move_type"].as<int>();
		time_ = in["move_type"].as<uint32_t>();
		vector_ = Vector2<int16_t>(in["vector"][0].as<int>(), in["vector"][1].as<int>());
	}

	ControlObjectMoveType type_;
	uint16_t time_;
	Vector2<int16_t> vector_;
};

class ControlObject
{
  public:
	ControlObject() {};
	ControlObject(MapObject* _mapobject) : mapobject_(_mapobject) {};
//	ControlObject(const ControlObject &_controlobject) : mapobject_(_controlobject.mapobject_) {};
	virtual ~ControlObject() {};

	virtual void Serialize(Serializer& out) {};

	virtual void Think() {};
	virtual ControlObjectMove Move() {};
	ControlObjectMove NextMove()
	{
		if(moves_.empty())
			Think();

		if(!moves_.empty())
			return moves_.front();

		return ControlObjectMove();
	};

	MapObject* mapobject_;
	// static std::vector<ControlObject*> controlobjects_;
	std::list<ControlObjectMove> moves_;
	// std::shared_ptr<MapObject> mapobject_;

	uint16_t id_;
	uint16_t remaining_time_;
};

#endif // TRON_RLENGINEX_CONTROLOBJECT_HH
