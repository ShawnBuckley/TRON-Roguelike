// TRON-Roguelike Game.hh

#ifndef ENGINEX_XGAME_HH
#define ENGINEX_XGAME_HH

#include <memory>

#include "entitymanager.hh"
#include "player.hh"

#include "io.hh"
#include "map.hh"
#include "worldtime.hh"

struct GameFlags
{
	GameFlags() : run_(1), paused_(0), realtime_(0) {};

	bool run_;
	bool paused_;
	bool realtime_;
};

class Game
{
  public:
	Game();

	void Start();
	void Run();
	void End();

	void Pause();

	void Save();
	void Load();

	void SetRealtime(bool _realtime);

	EntityManager entity_manager_;

	GameFlags game_flags_;

	std::unique_ptr<IO> io_;
	std::unique_ptr<Map> map_;
	std::unique_ptr<WorldTime> worldtime_;

	std::vector<std::shared_ptr<ControlObject> > entities_;

	std::shared_ptr<Player> player_;
};

#endif
