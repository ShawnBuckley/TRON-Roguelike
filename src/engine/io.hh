// TRON-Rouglike IO.hh

#ifndef TRON_RLENGINEX_IO_HH
#define TRON_RLENGINEX_IO_HH

#include <cstdint>
#include <memory>
#include <string>

#include "math/axisaligned_rectangle2.hh"

class DisplayObject;
class Color;

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

	std::shared_ptr<Color> old_color_;
	AxisAligned_Rectangle2<int16_t> viewport_;
};

#endif // TRON_RLENGINEX_IO_HH