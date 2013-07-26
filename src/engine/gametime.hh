// TRON-Roguelike GameTime.hh

#ifndef TRON_RLENGINEX_GAMETIME_HH
#define TRON_RLENGINEX_GAMETIME_HH

#include <inttypes.h>

class GameTime
{
  public:
	GameTime();
	virtual ~GameTime() {};

	void GameTurn(uint16_t _time);

	uint64_t tick_;
};


#endif // TRON_RLENGINEX_GAMETIME_HH
