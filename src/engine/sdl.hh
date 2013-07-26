// TRON-Rouglike SDL.hh

#ifndef TRON_RLENGINEX_SDL_HH
#define TRON_RLENGINEX_SDL_HH

#include <SDL/SDL.h>

#include <cstdint>
#include <string>
#include <vector>
#include "io.hh"

class Color;
class DisplayObject;

class SDL : public IO
{
  private:
	
  public:
	SDL() : screen_(NULL) {};
	virtual ~SDL();

	virtual void Init();

	void SetRealtime(bool _realtime) { realtime_ = _realtime; };
	bool LoadTexture(std::string _file);
	void LoadFont(int _x, int _y, int _xwdith, int _yhieght);
	
	uint32_t Input();
	
	void Render(const DisplayObject& _displayobject);
	void AddSpace();
	void NewLine();
	void Move(int16_t _y, int16_t _x);

	virtual void SetState() {};
	virtual void EndState() {};
	virtual void Clear();
	virtual void Refresh();
	virtual void SetColor(std::shared_ptr<Color> _color) {};
	virtual void Print(uint8_t _print, uint8_t _color);
	
	void Map();

	
	uint8_t xwidth_;
	uint8_t yheight_;

	SDL_Rect offset_;
	std::vector<SDL_Rect> character_; 
	SDL_Surface *screen_;
	std::vector<SDL_Surface*> texture_;
};

#endif // TRON_RLENGINEX_SDL_HH
