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
  	TronSerializer() {};
  	TronSerializer(const YAML::Node& in);

  	void Serialize(const TRON& in);

	void Serialize(const AiBike& in);
	void Serialize(const Bike& in);

	void Serialize(const LightGrid& out);
	void Serialize(const LightWall& out);


	TRON* UnserializeTRON(const YAML::Node& in);

	AiBike* UnserializeAiBike(const YAML::Node& in);
	Bike* UnserializeBike(const YAML::Node& in);

	LightWall* UnserializeLightWall(const YAML::Node& in);

	void LoadMapObjects(const YAML::Node& in);
	void LoadControlObjects(const YAML::Node& in);
	void LoadTimeObjects(const YAML::Node& in);
	void LoadMap(const YAML::Node& in);
	void LoadSectors(const YAML::Node& in);

	friend class TRON;
};

#endif