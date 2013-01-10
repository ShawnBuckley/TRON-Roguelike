// TRON-Roguelike LightWall.cc

#include "lightwall.hh"
#include "bike.hh"
#include "maptile.hh"

LightWall::LightWall(std::shared_ptr<DisplayObject> _displayobject, std::shared_ptr<MapTile> _maptile, Bike *_bike)
{
	displayobject_ = _displayobject;
	flags_ = MapObjectFlags(1, 1, 1, 1);
	bike_ = _bike;
	Rez(_maptile);
};

void LightWall::Save(std::stringstream &_save)
{
	_save << "lightwall" << " " << "a" << " "
		<< (unsigned int)id_ << " "
		<< (unsigned int)bike_->id_ << " "
		<< (unsigned int)displayobject_->id_ << " "
		<< (unsigned int)maptile_->id_ << " "
		<< std::endl;
};

void LightWall::Load()
{
	
};
