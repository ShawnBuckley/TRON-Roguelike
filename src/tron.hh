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
  	TRON(TronSerializer& in);
  	~TRON() {};

	void Start();
	Player* AddPlayerBike(uint8_t _color);
	AiBike* AddAiBike(uint8_t _color);

	void SaveGame(std::string _name);

	friend class TronSerializer;
};

#endif // TRON_RLENGINEX_TRON_HH
