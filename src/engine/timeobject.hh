// TRON-Roguelike TimeObject.hh

#ifndef TRON_RLENGINEX_TIMEOBJECT_HH
#define TRON_RLENGINEX_TIMEOBJECT_HH

#include <cstdint>
#include <memory>
#include <list>

namespace YAML
{
	class Emitter;
	class Node;
};

class MapObject;
class ControlObject;
class Serializer;

class TimeObject
{
  public:
  	TimeObject() : linked_(0), speed_(0), time_(0), mapobject_(NULL), controlobject_(NULL) {};
	TimeObject(uint16_t _speed);
	TimeObject(const YAML::Node& in);
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

	friend class Serializer;
};

#endif // TRON_RLENGINEX_TIMEOBJECT_HH
