// RLengineX Object.hh

#ifndef RLENGINEX_OBJECT_HH
#define RLENGINEX_OBJECT_HH

#include <sstream>
#include <unordered_map>

class Object
{
  public:
	Object();
	~Object();

	void Link();
	void Unlink();

	virtual void Save(std::stringstream &_save)=0;
	virtual void Load()=0;


	static uint32_t id_count_;
	static std::unordered_map<uint32_t, Object*> map_;

	uint32_t id_;
};

#endif // RLENGINEX_OBJECT_HH
