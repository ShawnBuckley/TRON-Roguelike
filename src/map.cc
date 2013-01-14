// TRON-Roguelike Map.cc

#include <inttypes.h>

#include "map.hh"
#include "maptile.hh"
#include "sector.hh"

void Map::Save(std::stringstream &_save)
{
	_save << "map" << " "
		<< "a" << " "
		<< (unsigned int)id_ << " "
		<< (unsigned int)rectangle_.Vertex(0).x() << " "
		<< (unsigned int)rectangle_.Vertex(0).y() << " "
		<< (unsigned int)rectangle_.Width() << " "
		<< (unsigned int)rectangle_.Height() << " "
		<< std::endl;
}

void Map::GenerateSector(std::shared_ptr<Sector> _sector, AxisAligned_Rectangle2<int16_t> _rectangle)
{
	_sector->Generate(_sector, _rectangle);
	sector_.push_back(_sector);

	if(_rectangle.Vertex(0).x() < rectangle_.Vertex(0).x())
		rectangle_.Origin(Vector2<int16_t>((_rectangle.Vertex(0).x()), rectangle_.Vertex(0).y()));

	if(_rectangle.Vertex(0).y() < rectangle_.Vertex(0).y())
		rectangle_.Origin(Vector2<int16_t>((rectangle_.Vertex(0).x()), _rectangle.Vertex(0).y()));

	if(_rectangle.Width()+_rectangle.Vertex(0).x() > rectangle_.Width())
		rectangle_.Width(_rectangle.Width()+_rectangle.Vertex(0).x());

	if(_rectangle.Height()+_rectangle.Vertex(0).y() > rectangle_.Height())
		rectangle_.Height(_rectangle.Height()+_rectangle.Vertex(0).y());
}

std::shared_ptr<MapTile> Map::Tile(Vector2<int16_t> _coord)
{
	if(!CoordValid(_coord))
		return NULL;

	for(std::vector<std::shared_ptr<Sector> >::iterator sector = sector_.begin();
		sector != sector_.end(); ++sector)
	{
		if((*sector) != NULL)
		{
			if((*sector)->rectangle_.Intersect(_coord))
			{
				return (*sector)->tile_[_coord.x() - (*sector)->rectangle_.Vertex(0).x()][_coord.y()-(*sector)->rectangle_.Vertex(0).y()];
			}
		}
	}

	return NULL;
}
