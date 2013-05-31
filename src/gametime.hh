// TRON-Roguelike GameTime.hh

#ifndef TRON_RLENGINEX_GAMETIME_HH
#define TRON_RLENGINEX_GAMETIME_HH

#include <inttypes.h>

#include "gameobject.hh"

class GameTime : public GameObject
{
  public:
	GameTime();

  	virtual void Save(std::stringstream &_save);
  	virtual void Load() {};

	void GameTurn(uint16_t _time);

	uint64_t tick_;
};


#endif // TRON_RLENGINEX_GAMETIME_HH
