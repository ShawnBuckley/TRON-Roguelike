// TRON-Roguelike ControlObject.hh

#ifndef TRON_RLENGINEX_CONTROLOBJECT_HH
#define TRON_RLENGINEX_CONTROLOBJECT_HH

#include <cstdlib>
#include <memory>
#include <list>

#include "math/vector2.hh"

class MapObject;

enum ControlObjectMoveType
{
	COMT_NONE = 0,
	COMT_MOVEMENT = 1,
	COMT_WAIT,
	COMT_ABILITY,
	COMT_EQUIPMENT,
	COMT_ITEM,
};

class ControlObjectMove// : public GameObject
{
  public:
  	ControlObjectMove() {};
  	ControlObjectMove(ControlObjectMoveType _type, uint16_t _time, Vector2<int16_t> _location)
		: type_(_type), time_(_time), location_(_location) {};

	ControlObjectMoveType type_;
	uint16_t time_;
	Vector2<int16_t> location_;
};

class ControlObject
{
  public:
	ControlObject() {};
	ControlObject(MapObject* _mapobject) : mapobject_(_mapobject) {};
//	ControlObject(const ControlObject &_controlobject) : mapobject_(_controlobject.mapobject_) {};
	virtual ~ControlObject() {};

	virtual void Think(uint16_t _remaining_time) {};
	virtual ControlObjectMove Move() {};

	bool HasNextMove() { return !moves_.empty(); };
	ControlObjectMove NextMove() { return moves_.front(); };
	
	MapObject* mapobject_;
	// static std::vector<ControlObject*> controlobjects_;
	std::list<ControlObjectMove> moves_;
	// std::shared_ptr<MapObject> mapobject_;

	uint16_t remaining_time_;
};

#endif // TRON_RLENGINEX_CONTROLOBJECT_HH
