// TRON-Roguelike TronSerializerk.hh

#ifndef TRON_RLENGINEX_TRONSERIALIZER_HH
#define TRON_RLENGINEX_TRONSERIALIZER_HH

#include "engine/serializer.hh"

namespace YAML
{
	class Emitter;
	class Node;
};

class AiBike;
class Bike;

class LightGrid;
class LightWall;


class TronSerializer : public Serializer
{
  public:
	void Serialize(const AiBike& in);
	void Serialize(const Bike& in);

	void Serialize(const LightGrid& out);
	void Serialize(const LightWall& out);

	friend class TRON;
};

#endif