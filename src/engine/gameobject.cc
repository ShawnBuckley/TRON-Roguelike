// TRON-Roguelike GameObject.cc

#include "gameobject.hh"

uint32_t GameObject::id_count_ = 0;
std::unordered_map<uint32_t, GameObject*> GameObject::map_;

GameObject::GameObject()
{
	id_ = GameObject::id_count_++;

	Link();
}

GameObject::~GameObject()
{
	Unlink();
}

void GameObject::Link()
{
//	GameObject::map_.insert({id_, this});
}

void GameObject::Unlink()
{
//	GameObject::map_.erase(id_);
}
