// TRON-Roguelike TimeObject.hh

#ifndef TRON_RLENGINEX_TIMEOBJECT_HH
#define TRON_RLENGINEX_TIMEOBJECT_HH

#include <cstdint>
#include <memory>
#include <list>

class MapObject;
class ControlObject;
class Serializer;

class TimeObject
{
  public:
  	TimeObject() : id_(0), linked_(0), speed_(0), time_(0), mapobject_(NULL), controlobject_(NULL) {};
	TimeObject(uint16_t _speed);

	void Tick();

	uint16_t id_;
	bool linked_;
	uint16_t speed_;
	uint16_t time_;

	MapObject* mapobject_;
	ControlObject* controlobject_;

  private:
	TimeObject(uint16_t _id, bool _linked, uint16_t _speed, uint16_t _time,
		MapObject* _mapobject, ControlObject* _controlobject) :
			id_(_id), linked_(_linked), speed_(_speed), time_(_time),
			mapobject_(_mapobject), controlobject_(_controlobject) {};

  friend class Serializer;
};

#endif // TRON_RLENGINEX_TIMEOBJECT_HH
