// TRON-Roguelike Game.hh

#ifndef TRON_RLENGINEX_TRON_HH
#define TRON_RLENGINEX_TRON_HH

#include "aibike.hh"
#include "engine/game.hh"

namespace YAML
{
	class Emitter;
	class Node;
}

class TRON : public Game
{
  public:
  	TRON() {};
  	TRON(const YAML::Node& in);
  	~TRON() {};

  	void Serialize(YAML::Emitter& out);
	void UnserializeMapObjects(const YAML::Node& in);
	void UnserializeControlObjects(const YAML::Node& in);
	void UnserializeTimeObjects(const YAML::Node& in);
	void UnserializeMap(const YAML::Node& in);
	void UnserializeSectors(const YAML::Node& in);

	void Start();
	Player* AddPlayerBike(uint8_t _color);
	AiBike* AddAiBike(uint8_t _color);
};

#endif // TRON_RLENGINEX_TRON_HH
