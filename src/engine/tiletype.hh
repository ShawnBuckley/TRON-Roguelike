// TRON-Roguelike TileType.hh

#ifndef TRON_RLENGINEX_TILETYPE_HH
#define TRON_RLENGINEX_TILETYPE_HH

class DisplayObject;
class Serializer;

struct TileTypeFlags
{
	TileTypeFlags() : render_(1), solid_(0) {};
	TileTypeFlags(bool _render, bool _solid) : render_(_render), solid_(_solid) {};
	TileTypeFlags(const YAML::Node& in);

	inline bool operator==(const TileTypeFlags& _other) const;

	bool render_;
	bool solid_;

	friend class Serializer;
};

class TileType
{
  public:
  	TileType() {};
	TileType(DisplayObject* _displayobject) : displayobject_(_displayobject) {};
	TileType(const TileTypeFlags _flags) : flags_(_flags) {};
	TileType(DisplayObject* _displayobject, const TileTypeFlags _flags)
		: displayobject_(_displayobject), flags_(_flags) {};
	TileType(const YAML::Node& in);

	~TileType() {};

	bool operator==(const TileType &_other) const;

	uint16_t id_;
	TileTypeFlags flags_;
	DisplayObject* displayobject_;

	friend class Serializer;
};

#endif // TRON_RLENGINEX_TILETYPE_HH
