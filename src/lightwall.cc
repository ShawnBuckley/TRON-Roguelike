// TRON-Roguelike LightWall.cc

#include "lightwall.hh"
#include "bike.hh"
#include "maptile.hh"

LightWall::LightWall(std::shared_ptr<DisplayObject> _displayobject, MapLocation<int16_t> _location, Bike *_bike)
{
	displayobject_ = _displayobject;
	flags_ = MapObjectFlags(1, 1, 1, 1);
	bike_ = _bike;
	Rez(_location);
};

void LightWall::Save(std::stringstream &_save)
{
	_save << "lightwall" << " " << "a" << " "
		<< (unsigned int)id_ << " "
		<< (unsigned int)bike_->id_ << " "
		<< (unsigned int)displayobject_->id_ << " "
		<< (unsigned int)location_.id_ << " "
		<< std::endl;
};

void LightWall::Load()
{
	
};
