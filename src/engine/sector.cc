// TRON RLengineX Sector.cc

#include "sector.hh"
#include "maptile.hh"

Sector::Sector()
{
	kGround = std::shared_ptr<TileType>(
		new TileType(std::move(std::shared_ptr<DisplayObject>(new DisplayObject('.', 176, kColor[dark_blue])))
	));
}

std::shared_ptr<MapTile> Sector::Tile(Vector2<int16_t> _coord)
{
	if(0 <= _coord.x && _coord.x <=rectangle_.Width() && 0 <= _coord.y && _coord.y <= rectangle_.Height())
	{
		return tile_[_coord.x][_coord.y];
	}

	return NULL;
};

void Sector::Generate(std::shared_ptr<Sector> _this, AxisAligned_Rectangle2<int16_t> _rectangle)
{
	rectangle_ = _rectangle;

	tile_.reserve(rectangle_.Width());

	for(int16_t x=0; x<=rectangle_.Width(); ++x)
	{
		std::vector<std::shared_ptr<MapTile> > row;
		row.reserve(rectangle_.Height());

		for(int16_t y=0; y<=rectangle_.Height(); ++y)
		{
			row.push_back(std::shared_ptr<MapTile>(new MapTile(Vector2<int16_t>(x+rectangle_.Vertex(0).x, y+rectangle_.Vertex(0).y), _this, kGround)));
		}

		tile_.push_back(row);
	}
}

bool SectorGenerator::Tick()
{
	
}
