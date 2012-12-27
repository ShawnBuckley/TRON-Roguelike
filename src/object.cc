// RLengineX Object.cc

#include "object.hh"

uint32_t Object::id_count_ = 0;
std::unordered_map<uint32_t, Object*> Object::map_;

Object::Object()
{
	id_ = Object::id_count_++;

	Link();
}

Object::~Object()
{
	Unlink();
}

void Object::Link()
{
	Object::map_.insert({id_, this});
}

void Object::Unlink()
{
	Object::map_.erase(id_);
}
