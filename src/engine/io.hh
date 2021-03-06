// TRON-Rouglike IO.hh

#ifndef TRON_RLENGINEX_IO_HH
#define TRON_RLENGINEX_IO_HH

#include <cstdint>
#include <memory>
#include <string>
#include <list>
#include <vector>

#include "math/axisaligned_rectangle2.hh"


class DisplayObject;
class Color;
class MapObject;
class Serializer;

#define CURSES_MULTIPLIER 3.9215686274509803921

enum Colors
{
	black = 0,
	red,
	green,
	yellow,
	blue,
	magenta,
	dark_blue,
	white
};

struct Color
{
	Color(uint8_t _r, uint8_t _g, uint8_t _b) : r_(_r), g_(_g), b_(_b) {};

	uint8_t r_;
	uint8_t g_;
	uint8_t b_;
};

class IO
{
  public:
  	virtual void Serialize(Serializer& out) {};

	virtual void Init()=0;

	virtual void Input()=0;
	virtual void Map()=0;

	void SetFPS(float _fps) { fps_ = _fps; };


	float fps_;
  
	uint8_t x_;
	uint8_t y_;

	uint16_t camera_mapobject_id_;
	MapObject* camera_mapobject_;
	Vector2<int16_t> camera_location_;

	uint8_t old_color_;
	AxisAligned_Rectangle2<int16_t> viewport_;

	std::list<char> keystrokes_;



	std::vector<Color> colors_;

  friend class Serializer;
};

#endif // TRON_RLENGINEX_IO_HH
