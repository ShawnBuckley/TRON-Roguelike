// TRON-Roguelike TronSerializerk.hh

#ifndef TRON_RLENGINEX_TRONSERIALIZER_HH
#define TRON_RLENGINEX_TRONSERIALIZER_HH

#include "engine/serializer.hh"

namespace YAML
{
	class Emitter;
	class Node;
};

class TRON;

class AiBike;
class Bike;

class LightGrid;
class LightWall;


class TronSerializer : public Serializer
{
  public:
  	// void Serialize(const TRON& in);

	void Serialize(const AiBike& in);
	void Serialize(const Bike& in);

	void Serialize(const LightGrid& out);
	void Serialize(const LightWall& out);


	void Serialize(const ControlObjectMove& in) { Serializer::Serialize(in); };

	void Serialize(const DisplayObject& in) { Serializer::Serialize(in); };
	void Serialize(const TimeObject& in) { Serializer::Serialize(in); };

	void Serialize(const Game& in) { Serializer::Serialize(in); };

	void Serialize(const GameTime& in) { Serializer::Serialize(in); };

	void Serialize(const IO& in) { Serializer::Serialize(in); };

	void Serialize(const Map& in) { Serializer::Serialize(in); };

	void Serialize(const MapLocation& in) { Serializer::Serialize(in); };
	void Serialize(const MapObjectStats& in) { Serializer::Serialize(in); };
	void Serialize(const MapObjectFlags& in) { Serializer::Serialize(in); };
	void Serialize(const MapObjectMove& in) { Serializer::Serialize(in); };
	void Serialize(const MapObject& in) { Serializer::Serialize(in); };

	void Serialize(const MapTile& in) { Serializer::Serialize(in); };

	void Serialize(const Player& in) { Serializer::Serialize(in); };

	void Serialize(const TileTypeFlags& in) { Serializer::Serialize(in); };
	void Serialize(const TileType& in) { Serializer::Serialize(in); };

	void Serialize(const Sector& in) { Serializer::Serialize(in); };

	void Serialize(const WorldTime& in) { Serializer::Serialize(in); };

	friend class TRON;
};

#endif