// Rouglike EngineX IO.hh

#ifndef ENGINE_IO_HH
#define ENGINE_IO_HH

#include <cstdint>
#include <memory>
#include <string>

class DisplayObject;
class Color;

class IO
{
  private:	

  public:
	virtual void Init()=0;

	virtual bool Input()=0;
	virtual void Map()=0;

	void SetFPS(float _fps) { fps_ = _fps; };
	virtual void SetRealtime(bool _realtime)=0;


	bool realtime_;
	float fps_;
  
	uint8_t x_;
	uint8_t y_;

	std::shared_ptr<Color> old_color_;
};

#endif
