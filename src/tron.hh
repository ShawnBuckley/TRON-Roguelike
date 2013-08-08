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

class TronSerializer;

class TRON : public Game
{
  public:
  	TRON() { name_ = std::string("TRON"); };
  	TRON(const YAML::Node& in);
  	~TRON() {};

  	virtual std::string GameName() { return std::string("TRON"); };

  	void Serialize(YAML::Emitter& out);
	void UnserializeMapObjects(const YAML::Node& in);
	void UnserializeControlObjects(const YAML::Node& in);
	void UnserializeTimeObjects(const YAML::Node& in);
	void UnserializeMap(const YAML::Node& in);
	void UnserializeSectors(const YAML::Node& in);

	void Start();
	Player* AddPlayerBike(uint8_t _color);
	AiBike* AddAiBike(uint8_t _color);

	void SaveGame(std::string _name);

	friend class TronSerializer;
};

#endif // TRON_RLENGINEX_TRON_HH
