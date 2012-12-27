// RLengineX GameTime.hh

#ifndef RLENGINEX_GAMETIME_HH
#define RLENGINEX_GAMETIME_HH

#include <inttypes.h>

#include "object.hh"

class GameTime : public Object
{
  public:
	GameTime();

  	virtual void Save(std::stringstream &_save);
  	virtual void Load() {};

	void GameTurn(uint16_t _time);

	uint64_t tick_;
};


#endif
