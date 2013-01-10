// TRON-Roguelike EntityManager.hh

#include <memory>

#include "aibike.hh"
#include "bike.hh"
#include "mapobject.hh"
#include "player.hh"

class EntityManager
{
  public:
	EntityManager() {};
	~EntityManager() {};

	std::shared_ptr<Player> AddPlayerMapobject(Colors _color);
	std::shared_ptr<Player> AddPlayerBike(Colors _color);
	std::shared_ptr<AiBike> AddAiBike(Colors _color);
};
