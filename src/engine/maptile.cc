// TRON-Roguelike MapTile.hh

#include "maptile.hh"
#include "tiletype.hh"
#include "mapobject.hh"

std::vector<MapObject*> MapTile::SolidMapObject()
{
	std::vector<MapObject*> result;

	if(mapobject_list_.empty())
		return result;

	for(auto mapobject = mapobject_list_.begin(); mapobject != mapobject_list_.end(); ++mapobject)
	{
		if(*mapobject == NULL) continue;

		if((*mapobject)->flags_.clipping_)
		{
			result.push_back(*mapobject);
		}
	}

	return result;
}

bool MapTile::AnySolidMapObject()
{
	if(mapobject_list_.empty())
		return 0;

	for(auto mapobject = mapobject_list_.begin(); mapobject != mapobject_list_.end(); ++mapobject)
	{
		if(*mapobject == NULL) continue;

		if((*mapobject)->flags_.clipping_)
		{
			return 1;
		}
	}

	return 0;
}

std::shared_ptr<DisplayObject> MapTile::VisibleMapObject()
{
	if(mapobject_list_.empty()) return NULL;

	for(auto mapobject = mapobject_list_.begin(); mapobject != mapobject_list_.end(); ++mapobject)
	{
		if((*mapobject) == NULL) continue;

		if((*mapobject)->flags_.visible_)
		{
			return (*mapobject)->displayobject_;
		}
	}

	return NULL;
}
