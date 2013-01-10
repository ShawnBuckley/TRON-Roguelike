// TRON-Roguelike LightGrid.hh

#ifndef TRONLIKE_XLIGHTGRID_HH
#define TRONLIKE_XLIGHTGRID_HH

#include <memory>

#include "tiletype.hh"
#include "map.hh"

class LightGrid : public Map
{
	~LightGrid() {};

  	void Save(std::stringstream &_save);
  	void Load() {};

	void Gen(uint8_t z, uint8_t y, uint8_t x);
//	bool Fill(uint8_t Size);

	std::shared_ptr<TileType> kFloor[4];
	std::shared_ptr<TileType> kWall;
};

#endif
