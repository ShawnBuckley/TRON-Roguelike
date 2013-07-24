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
  private:	

  public:
	virtual void Init()=0;

	virtual uint32_t Input()=0;
	virtual void Map()=0;

	void SetFPS(float _fps) { fps_ = _fps; };
	virtual void SetRealtime(bool _realtime)=0;


	bool realtime_;
	float fps_;
  
	uint8_t x_;
	uint8_t y_;

	std::list<char> keystrokes_;

	std::shared_ptr<Color> old_color_;
	AxisAligned_Rectangle2<int16_t> viewport_;

	std::vector<Color> colors_;
};

#endif // TRON_RLENGINEX_IO_HH
