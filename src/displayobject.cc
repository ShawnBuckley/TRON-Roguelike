// TRON RlengineX DisplayObject.cc

#include "displayobject.hh"

void DisplayObject::Save(std::stringstream &_save)
{
	_save << "displayobject" << " "
		<< "a" << " "
		<< (unsigned int)id_ << " "
		<< print_ << " "
		<< (unsigned int)sprite_ << " "
		<< (unsigned int)color_->id_ << " "
		<< std::endl;
}

void DisplayObject::Load()
{

}
