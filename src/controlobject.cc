// TRON RLengineX ControlObject.cc

#include "controlobject.hh"
#include "mapobject.hh"

void ControlObject::Save(std::stringstream &_save)
{
	_save << "controlobject" << " "
		<< "a" << " "
		<< (unsigned int)mapobject_->id_ << " "
		<< std::endl;
}

void ControlObject::Load()
{

}
