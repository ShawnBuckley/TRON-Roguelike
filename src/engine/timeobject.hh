// TRON-Roguelike TimeObject.hh

#ifndef TRON_RLENGINEX_TIMEOBJECT_HH
#define TRON_RLENGINEX_TIMEOBJECT_HH

#include <cstdint>
#include <memory>
#include <list>

class MapObject;
class ControlObject;

class TimeObject
{
  public:
  	TimeObject() : linked_(0), speed_(0), time_(0) {};
	TimeObject(uint16_t _speed);
	TimeObject(uint16_t _speed, std::shared_ptr<MapObject> _mapobject, std::shared_ptr<ControlObject> _controlobject);
	~TimeObject();

	void TimeLink();
	void TimeUnlink();

	void Tick();

	static std::list<TimeObject*> timeobjects_;

	bool linked_;
	uint16_t speed_;
	uint16_t time_;

	MapObject* mapobject_;
	ControlObject* controlobject_;
};

#endif // TRON_RLENGINEX_TIMEOBJECT_HH
