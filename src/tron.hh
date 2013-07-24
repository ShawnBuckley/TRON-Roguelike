// TRON-Roguelike Game.hh

#ifndef TRON_RLENGINEX_TRON_HH
#define TRON_RLENGINEX_TRON_HH

#include "aibike.hh"
#include "engine/game.hh"

class TRON : public Game
{
  public:
  	TRON() {};
  	~TRON() {};

	void Start();
	Player* AddPlayerBike(uint8_t _color);
	AiBike* AddAiBike(uint8_t _color);
};

#endif // TRON_RLENGINEX_TRON_HH
