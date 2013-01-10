// TRON-Roguelike LightGrid.cc

#include "color.hh"
#include "lightgrid.hh"
#include "maptile.hh"
#include "tiletype.hh"

void LightGrid::Save(std::stringstream &_save)
{
	_save << "lightgrid" << " "
		<< "a" << " "
		<< (unsigned int)id_ << " "
		<< (unsigned int)x_ << " "
		<< (unsigned int)y_ << " "
		<< (unsigned int)z_ << " "
		<< (unsigned int)size_ << " ";
		for(uint8_t i=0; i<5; ++i) 
			_save << (unsigned int)kFloor[i]->id_ << " ";
		_save << (unsigned int)kWall->id_ << " "
		<< std::endl;
}

void LightGrid::Gen(uint8_t _z, uint8_t _y, uint8_t _x)
{
	kFloor[0] = std::shared_ptr<TileType>(
		new TileType(std::move(std::shared_ptr<DisplayObject>(new DisplayObject('+', 197, kColor[dark_blue])))
	));

	kFloor[1] = std::shared_ptr<TileType>(
		new TileType(std::move(std::shared_ptr<DisplayObject>(new DisplayObject('-', 196, kColor[dark_blue])))
	));

	kFloor[2] = std::shared_ptr<TileType>(
		new TileType(std::move(std::shared_ptr<DisplayObject>(new DisplayObject('|', 179, kColor[dark_blue])))
	));

	kFloor[3] = std::shared_ptr<TileType>(
		new TileType(std::move(std::shared_ptr<DisplayObject>(new DisplayObject(' ', 255, kColor[black])))
	));

	kWall = std::shared_ptr<TileType>(
		new TileType(std::move(std::shared_ptr<DisplayObject>(new DisplayObject('#', 219, kColor[dark_blue]))),
		TileTypeFlags(1, 1)
	));

	z_ = _z;
	y_ = _y;
	x_ = _x;
	
	tile_.reserve(x_);

	for(uint8_t x=0; x<x_; ++x)
	{
		std::vector<std::shared_ptr<MapTile> > row;
		row.reserve(y_);

		for(uint8_t y=0; y<y_; ++y)
		{
			if(y ==0 || y == y_-1 || x == 0 || x == x_-1)
				row.push_back(std::move(std::shared_ptr<MapTile>(new MapTile(Coord2<uint8_t>(x, y), kWall))));
			else
			{
				if(y % 2)
				{
					if(x % 2)
						row.push_back(std::move(std::shared_ptr<MapTile>(new MapTile(Coord2<uint8_t>(x, y), kFloor[0]))));
					else
						row.push_back(std::move(std::shared_ptr<MapTile>(new MapTile(Coord2<uint8_t>(x, y), kFloor[1]))));
				}
				else
				{
					if(x % 2)
						row.push_back(std::move(std::shared_ptr<MapTile>(new MapTile(Coord2<uint8_t>(x, y), kFloor[2]))));
					else
						row.push_back(std::move(std::shared_ptr<MapTile>(new MapTile(Coord2<uint8_t>(x, y), kFloor[3]))));
				}
			}
		}

		tile_.push_back(std::move(row));
	}
}
