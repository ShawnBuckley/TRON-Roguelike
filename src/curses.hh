// Rouglike EngineX xDisplay.hh

#ifndef ENGINE_XCURSES_HH
#define ENGINE_XCURSES_HH

#include <curses.h>

#include "io.hh"

class Color;
class DisplayObject;

class Curses : public IO
{
  private:
	
  public:
	Curses() : window_(NULL) {};
	~Curses();

	void SetRealtime(bool _realtime);
	void Init();
	void LoadColors();

	bool Input();

	void Clear();
	void Refresh();
	void SetColor(std::shared_ptr<Color> _color);
	void EndColor(std::shared_ptr<Color> _color);
	void Render(const DisplayObject *_displayobject);
	void Print(uint8_t _print, std::shared_ptr<Color> _color);
	void AddSpace();
	void NewLine();
	void Move(uint8_t _y, uint8_t _x);

	void Map();


	bool color_;
	WINDOW* window_;
};

#endif
