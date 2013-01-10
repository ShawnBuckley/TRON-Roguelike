// TRON-Roguelike Map.cc

#include <inttypes.h>

#include "map.hh"
#include "maptile.hh"

Map::Map() : x_(0), y_(0), z_(0), size_(0) {}

void Map::Save(std::stringstream &_save)
{
	_save << "map" << " "
		<< "a" << " "
		<< (unsigned int)id_ << " "
		<< (unsigned int)x_ << " "
		<< (unsigned int)y_ << " "
		<< (unsigned int)z_ << " "
		<< (unsigned int)size_ << " "
		<< (unsigned int)kGround->id_ << " "
		<< std::endl;
}

void Map::Gen(uint8_t _z, uint8_t _y, uint8_t _x)
{
	kGround = std::shared_ptr<TileType>(
		new TileType(std::move(std::shared_ptr<DisplayObject>(new DisplayObject('.', '.', kColor[white])))
	));

	uint8_t x;
	uint8_t y;

	z_ = _z;
	y_ = _y;
	x_ = _x;
	
	for(x=0; x<x_; ++x)
	{
		std::vector<std::shared_ptr<MapTile> > row;
		row.reserve(y_);
	
		for(y=0; y<_y; ++y)
		{
			row.push_back(std::shared_ptr<MapTile>(new MapTile(Coord2<uint8_t>(x, y), kGround)));
		}
		
		tile_.push_back(row);
	}
}
