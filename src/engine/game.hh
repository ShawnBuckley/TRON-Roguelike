// TRON-Roguelike Game.hh

#ifndef TRON_RLENGINEX_GAME_HH
#define TRON_RLENGINEX_GAME_HH

#include <unordered_map>
#include <iostream>
#include <typeinfo>
#include <memory>
#include <vector>
#include <list>

#include "player.hh"


#include "io.hh"
#include "map.hh"
#include "worldtime.hh"

namespace YAML
{
	class Emitter;
	class Node;
}

class Serializer;

class Game
{
  public:
	Game();
	Game(const YAML::Node& in);
	virtual ~Game() {};

	const std::string& GameName() const { return name_; };

	virtual void Start();
	void Run();
	void End();

	void Pause();

	void Save();
	virtual void SaveGame(std::string);
	void Load();

	void SetPaused(bool _paused);
	void SetRealtime(bool _realtime);

	DisplayObject* AddDisplayObject(const DisplayObject _displayobject);
	DisplayObject* GetDisplayObject(const uint16_t _id);

	TileType* AddTileType(const TileType _tiletype);
	TileType* GetTileType(uint16_t _id);
	
	uint16_t AddMapObject(MapObject* _mapobject);
	MapObject* GetMapObject(uint16_t _id);

	uint16_t AddTimeObject(TimeObject* _timeobject);
	TimeObject* GetTimeObject(uint16_t _id);

	uint16_t AddControlObject(ControlObject* _controlobject);
	ControlObject* GetControlObject(uint16_t _id);

	uint16_t AddPlayer(Player* _player);
	Player* AddPlayerMapobject(uint8_t _color);

	void RemoveMapObject(uint16_t _id);
	void RemoveMapObject(MapObject* _mapobject);

	void RemoveTimeObject(uint16_t _id);
	void RemoveTimeObject(TimeObject* _timeobject);

	void RemoveControlObject(uint16_t _id);
	void RemoveControlObject(ControlObject* _controlobject);

	std::string name_;
	std::string version_;

	bool run_;
	bool paused_;
	bool realtime_;

	std::vector<Player*> players_;

	std::unique_ptr<IO> io_;
	std::unique_ptr<Map> map_;
	std::unique_ptr<GameTime> time_;

	std::vector<std::unique_ptr<DisplayObject>> displayobjects_;
	std::list<uint16_t> displayobject_open_id_;

	std::vector<std::unique_ptr<TileType>> tiletypes_;
	std::list<uint16_t> tiletype_open_id_;

	std::vector<std::unique_ptr<MapObject>> mapobjects_;
	std::list<uint16_t> mapobject_open_id_;

	std::vector<std::unique_ptr<TimeObject>> timeobjects_;
	std::list<uint16_t> timeobject_open_id_;

	std::vector<std::unique_ptr<ControlObject>> controlobjects_;
	std::list<uint16_t> controlobject_open_id_;

	friend class Serializer;
};

Game& game();

#endif // TRON_RLENGINEX_GAME_HH
