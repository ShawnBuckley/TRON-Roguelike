// TRON-Roguelike TileType.hh

#ifndef TRON_RLENGINEX_TILETYPE_HH
#define TRON_RLENGINEX_TILETYPE_HH

class DisplayObject;
class Serializer;

struct TileTypeFlags
{
	TileTypeFlags() : render_(1), solid_(0) {};
	TileTypeFlags(bool _render, bool _solid) : render_(_render), solid_(_solid) {};

	inline bool operator==(const TileTypeFlags& _other) const
	{
		return (render_ == _other.render_ && solid_ == _other.solid_);
	};

	bool render_;
	bool solid_;
};


class TileType
{
  public:
  	TileType() {};
	TileType(DisplayObject* _displayobject) : displayobject_(_displayobject) {};
	TileType(const TileTypeFlags _flags) : flags_(_flags) {};
	TileType(DisplayObject* _displayobject, const TileTypeFlags _flags)
		: displayobject_(_displayobject), flags_(_flags) {};

	~TileType() {};

	bool operator==(const TileType &_other) const
	{
		return (flags_ == _other.flags_ && displayobject_ == _other.displayobject_);
	};

	uint16_t id_;
	TileTypeFlags flags_;
	DisplayObject* displayobject_;

  // private:
	TileType(uint16_t _id, DisplayObject* _displayobject,
		const TileTypeFlags _flags) : displayobject_(_displayobject),
		flags_(_flags) {};

	friend class Serializer;
};

#endif // TRON_RLENGINEX_TILETYPE_HH
