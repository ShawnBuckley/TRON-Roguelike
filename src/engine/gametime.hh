// TRON-Roguelike GameTime.hh

#ifndef TRON_RLENGINEX_GAMETIME_HH
#define TRON_RLENGINEX_GAMETIME_HH

#include <inttypes.h>

class GameTime
{
  public:
	GameTime();
	virtual ~GameTime() {};

	uint64_t TickCount() { return tick_; };

	virtual uint16_t Turn();

	uint64_t tick_;
};


#endif // TRON_RLENGINEX_GAMETIME_HH
