// TRON-Roguelike Game.hh

#ifndef TRON_RLENGINEX_GAME_HH
#define TRON_RLENGINEX_GAME_HH

#include <unordered_map>
#include <iostream>
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

class Game
{
  public:
	Game();
	Game(const YAML::Node& in);
	virtual ~Game() {};

	virtual void Serialize(YAML::Emitter& out);
	virtual void UnserializeGameTime(const YAML::Node& in);
	virtual void UnserializeDisplayObjects(const YAML::Node& in);
	virtual void UnserializeTileTypes(const YAML::Node& in);
	virtual void UnserializeMapObjects(const YAML::Node& in);
	virtual void UnserializeControlObjects(const YAML::Node& in);
	virtual void UnserializeTimeObjects(const YAML::Node& in);
	virtual void UnserializeMap(const YAML::Node& in);
	virtual void UnserializeMapLoactions(const YAML::Node& in);

	virtual void Start();
	void Run();
	void End();

	void Pause();

	void Save();
	void SaveGame(std::string _save);
	void Load();

	void SetRealtime(bool _realtime);

	DisplayObject* AddDisplayObject(const DisplayObject _displayobject);
	DisplayObject* GetDisplayObject(const uint16_t _id);

	TileType* AddTileType(const TileType _tiletype);
	TileType* GetTileType(uint16_t _id);
	
	uint16_t AddMapObject(MapObject* _mapobject);
	MapObject* GetMapObject(uint16_t _id);

	uint16_t AddControlObject(ControlObject* _controlobject);
	ControlObject* GetControlObject(uint16_t _id);

	uint16_t AddPlayer(Player* _player);
	Player* AddPlayerMapobject(uint8_t _color);

	void RemoveMapObject(uint16_t _id);
	void RemoveMapObject(MapObject* _mapobject);

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

	std::vector<std::unique_ptr<ControlObject>> entities_;
	std::list<uint16_t> entity_open_id_;

	// std::vector<std::unique_ptr<ControlObject>> controlobjects_;
};

Game& game();

#endif // TRON_RLENGINEX_GAME_HH
