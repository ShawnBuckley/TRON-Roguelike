/* TRON on Roguelike EngineX

	Requires:
		G++ 4.6.2+
		ncurses
		SDL-1.2
		libPNG
		OpenGL

	The game happens on a TRON Lightcycle grid.  The only objective is to box
	your opponent in before it does the same to you.
	
	The Player's lightcycle (blue) is controlled with VI-keys.
*/

#include "game.hh"
#include "rng.hh"

Game game;
RNG rng;

int main(int argc, char **argv)
{
	game.Start();

	return 0;
}
