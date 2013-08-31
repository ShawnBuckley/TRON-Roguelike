// TRON-Roguelike GameTime.hh

#ifndef TRON_RLENGINEX_GAMETIME_HH
#define TRON_RLENGINEX_GAMETIME_HH

#include <inttypes.h>

namespace YAML
{
	class Emitter;
	class Node;
};

class Serializer;

class GameTime
{
  public:
	GameTime() : tick_(0) {};
	virtual ~GameTime() {};

	virtual void Serialize(Serializer& out) const; 

	uint64_t TickCount() { return tick_; };

	virtual uint16_t Turn();

  protected:
	uint64_t tick_;	

  private:
	GameTime(uint64_t _tick) : tick_(_tick) {};

	friend class Serializer;
};

#endif // TRON_RLENGINEX_GAMETIME_HH
