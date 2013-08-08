// TRON-Roguelike LightGrid.hh

#ifndef TRON_RLENGINEX_LIGHTGRID_HH
#define TRON_RLENGINEX_LIGHTGRID_HH

#include <memory>

#include "engine/tiletype.hh"
#include "engine/sector.hh"

namespace YAML
{
	class Emitter;
	class Node;
}

class TronSerializer;

class LightGrid : public Sector
{
  public:
  	LightGrid() {};
	LightGrid(const YAML::Node& in);
	~LightGrid() {};

	void Serialize(Serializer& out);

	void Generate(AxisAligned_Rectangle2<int16_t> _rectangle);
//	bool Fill(uint8_t Size);

	friend class TronSerializer;
};

#endif // TRON_RLENGINEX_LIGHTGRID_HH
