// TRON-Roguelike LightGrid.cc

#include "engine/color.hh"
#include "engine/maptile.hh"
#include "engine/tiletype.hh"

#include "lightgrid.hh"

LightGrid::LightGrid()
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
}

void LightGrid::Generate(std::shared_ptr<Sector> _this, AxisAligned_Rectangle2<int16_t> _rectangle)
{
	rectangle_ = _rectangle;

	tile_.reserve(rectangle_.Width());

	for(int16_t x=0; x<=rectangle_.Width(); ++x)
	{
		std::vector<std::shared_ptr<MapTile> > row;
		row.reserve(rectangle_.Height());

		for(int16_t y=0; y<=rectangle_.Height(); ++y)
		{
			Vector2<int16_t> location(x+rectangle_.Vertex(0).x, y+rectangle_.Vertex(0).y);
		
			if(y == 0 || y >= rectangle_.Height()-1 || x == 0 || x >= rectangle_.Width()-1)
				row.push_back(std::move(std::shared_ptr<MapTile>(new MapTile(location, _this, kWall))));
			else
			{
				if(y % 2)
				{
					row.push_back(std::move(std::shared_ptr<MapTile>(new MapTile(location, _this, x % 2 ? kFloor[0] : kFloor[1]))));
				}
				else
				{
					row.push_back(std::move(std::shared_ptr<MapTile>(new MapTile(location, _this, x % 2 ? kFloor[2] : kFloor[3]))));
				}
			}
		}

		tile_.push_back(std::move(row));
	}
	
	printf("LG %p: %li %li\n", this, tile_.size(), tile_[0].size());
}
