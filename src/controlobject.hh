// TRON-Roguelike ControlObject.hh

#ifndef TRON_RLENGINEX_CONTROLOBJECT_HH
#define TRON_RLENGINEX_CONTROLOBJECT_HH

#include <cstdlib>
#include <memory>
#include <list>

#include "math/vector2.hh"

#include "gameobject.hh"

class MapObject;

enum ControlObjectMoveType
{
	COMT_MOVEMENT = 0,
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

class ControlObject : public GameObject
{
  public:
	ControlObject() {};
//	ControlObject(const ControlObject &_controlobject) : mapobject_(_controlobject.mapobject_) {};
	~ControlObject() {};

  	virtual void Save(std::stringstream &_save);
  	virtual void Load();

	virtual void Think(uint16_t _remaining_time)=0;
	virtual ControlObjectMove Move()=0;

	bool HasNextMove() { return !moves_.empty(); };
	ControlObjectMove NextMove() { return moves_.front(); };
	
	// static std::vector<ControlObject*> controlobjects_;
	std::list<ControlObjectMove> moves_;
	std::shared_ptr<MapObject> mapobject_;

	uint16_t remaining_time_;
};

#endif // TRON_RLENGINEX_CONTROLOBJECT_HH
