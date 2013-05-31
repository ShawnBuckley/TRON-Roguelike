// TRON-Roguelike GameObject.hh

#ifndef TRON_RLENGINEX_OBJECT_HH
#define TRON_RLENGINEX_OBJECT_HH

#include <sstream>
#include <unordered_map>

class GameObject
{
  public:
	GameObject();
	~GameObject();

	void Link();
	void Unlink();

	virtual void Save(std::stringstream &_save)=0;
	virtual void Load()=0;


	static uint32_t id_count_;
	static std::unordered_map<uint32_t, GameObject*> map_;

	uint32_t id_;
};

#endif // TRON_RLENGINEX_OBJECT_HH
