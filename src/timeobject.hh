// TRON-Roguelike TimeObject.hh

#ifndef TRON_RLENGINEX_TIMEOBJECT_HH
#define TRON_RLENGINEX_TIMEOBJECT_HH

#include <cstdint>
#include <memory>
#include <list>

#include "object.hh"

class MapObject;
class ControlObject;

class TimeObject : public Object
{
  public:
	TimeObject(uint16_t _speed);
	TimeObject(uint16_t _speed, std::shared_ptr<MapObject> _mapobject, std::shared_ptr<ControlObject> _controlobject);
	~TimeObject();

  	void Save(std::stringstream &_save);
  	void Load() {};

	void TimeLink();
	void TimeUnlink();

	void Tick();

	static std::list<TimeObject*> list_;

	bool linked_;
	uint16_t speed_;
	uint16_t time_;

	std::shared_ptr<MapObject> mapobject_;
	std::shared_ptr<ControlObject> controlobject_;
};

#endif // TRON_RLENGINEX_TIMEOBJECT_HH
