// TRON-Rogulike MapLocation.hh

#ifndef TRON_RLENGINEX_MAPLOCATION_HH
#define TRON_RLENGINEX_MAPLOCATION_HH

#include <vector>

#include <yaml-cpp/yaml.h>

#include "math/axisaligned_rectangle2.hh"

#include "maptile.hh"

class MapLocation
{
  public:
	MapLocation() {};
	MapLocation(AxisAligned_Rectangle2<int16_t> _rectangle) : rectangle_(_rectangle)
	{
		maptile_.reserve(rectangle_.Width());
	
		for(int16_t x=0; x<=rectangle_.Width(); ++x)
		{
			std::vector<MapTile*> row;
			row.reserve(rectangle_.Height());
			maptile_.push_back(row);
		}
	};

	void Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "type";
		out << YAML::Value << "MapLocation";
		out << YAML::Key << "rectangle";
		out << YAML::Flow;
		out << YAML::BeginSeq;
		out << YAML::Key << rectangle_.Vertex(0).x;
		out << YAML::Key << rectangle_.Vertex(0).y;
		out << YAML::Key << rectangle_.Width();
		out << YAML::Key << rectangle_.Height();
		out << YAML::EndSeq;

/*		std::size_t x_limit = maptile_.size();
		for(std::size_t x=0; x<x_limit; x++)
		{
			out << YAML::BeginSeq;

			std::size_t y_limit = maptile_[x].size();
			for(std::size_t y=0; y<y_limit; y++)
			{
				MapTile& tile = *maptile_[x][y];

				out << YAML::Flow;
				out << YAML::BeginSeq;
				out << tile.location_.x;
				out << tile.location_.y;
				out << YAML::EndSeq;
			}

			out << YAML::EndSeq;
		}*/

		out << YAML::EndMap;
	};

	std::vector<std::vector<MapTile*>> maptile_;
	AxisAligned_Rectangle2<int16_t> rectangle_;

 	void Save(std::stringstream &_save) {};
  	void Load() {};
};

#endif // TRON_RLENGINEX_MAPLOCATION_HH

