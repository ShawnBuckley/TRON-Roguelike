// TRON-Roguelike ControlObject.hh

#ifndef TRON_RLENGINEX_CONTROLOBJECT_HH
#define TRON_RLENGINEX_CONTROLOBJECT_HH

#include <cstdlib>
#include <memory>
#include <list>

#include "object.hh"

class MapObject;

class ControlObject : public Object
{
  public:
	ControlObject() {};
//	ControlObject(const ControlObject &_controlobject) : mapobject_(_controlobject.mapobject_) {};
	~ControlObject() {};

  	virtual void Save(std::stringstream &_save);
  	virtual void Load();

	virtual void Think() {};
	
	static std::list<ControlObject*> list_;
	std::shared_ptr<MapObject> mapobject_;
};

#endif // TRON_RLENGINEX_CONTROLOBJECT_HH
