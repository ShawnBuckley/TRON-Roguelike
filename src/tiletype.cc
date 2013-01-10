// TRON-Roguelike TileType.hh

#include "tiletype.hh"

void TileType::Save(std::stringstream &_save)
{
	_save << "tiletype" << " "
		<< "a" << " "
		<< (unsigned int)id_ << " "
		<< (unsigned int)tiletype_flags_.render_ << " "
		<< (unsigned int)tiletype_flags_.solid_ << " "
		<< (unsigned int)displayobject_->id_ << " "
		<< std::endl;
} 
