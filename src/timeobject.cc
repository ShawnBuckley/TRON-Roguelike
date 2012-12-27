// RLengineX TimeObject.cc

#include "timeobject.hh"
#include "controlobject.hh"
#include "mapobject.hh"


std::list<TimeObject*> TimeObject::list_;

TimeObject::TimeObject(uint16_t _speed)
	: speed_(_speed), time_(0) {}

TimeObject::TimeObject(uint16_t _speed, std::shared_ptr<MapObject> _mapobject, std::shared_ptr<ControlObject> _controlobject)
	: speed_(_speed), time_(0) {}

TimeObject::~TimeObject()
{
	if(linked_)
		TimeUnlink();
}

void TimeObject::Save(std::stringstream &_save)
{
	_save << "timeobject" << " "
		<< "a" << " "
		<< (unsigned int)id_ << " "
		<< linked_ << " "
		<< (unsigned int)speed_ << " "
		<< (unsigned int)time_ << " "
		<< (unsigned int)mapobject_->id_ << " "
		<< (unsigned int)controlobject_->id_ << " "
		<< std::endl;
}

void TimeObject::TimeLink()
{
	TimeObject::list_.push_back(this);
	
	linked_ = 1;
}

void TimeObject::TimeUnlink()
{
	printf("Time unlink %p\n", this);
	
	TimeObject::list_.remove(this);
	
	linked_ = 0;
}
