// TRON-Roguelike MapTile.hh

#include "maptile.hh"
#include "tiletype.hh"
#include "mapobject.hh"

void MapTile::Save(std::stringstream &_save)
{
	_save << "maptile" << " "
		<< "a" << " "
		<< (unsigned int)id_ << " "
		<< (unsigned int)location_.x() << " "
		<< (unsigned int)location_.y() << " "
		<< tiletype_->id_ << " "
		<< (unsigned int)mapobject_list_.size() << " ";
	for(std::list<MapObject*>::iterator it = mapobject_list_.begin(); it != mapobject_list_.end(); ++it)
		_save << (unsigned int)((*it)->id_) << " ";
	_save << std::endl;
}

std::vector<MapObject*> MapTile::SolidMapObject()
{
	std::vector<MapObject*> result;

	if(mapobject_list_.empty())
		return result;

	for(std::list<MapObject*>::iterator mapobject = mapobject_list_.begin(); mapobject != mapobject_list_.end(); ++mapobject)
	{
		if(*mapobject == NULL) continue;

		if((*mapobject)->flags_.clipping_)
		{
			result.push_back(*mapobject);
		}
	}

	return result;
}

std::shared_ptr<DisplayObject> MapTile::VisibleMapObject()
{
	if(mapobject_list_.empty()) return NULL;

	for(std::list<MapObject*>::iterator mapobject = mapobject_list_.begin(); mapobject != mapobject_list_.end(); ++mapobject)
	{
		if((*mapobject) == NULL) continue;

		if((*mapobject)->flags_.visible_)
		{
			return (*mapobject)->displayobject_;
		}
	}

	return NULL;
}
