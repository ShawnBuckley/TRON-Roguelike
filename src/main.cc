// TRON-Roguelike Main.cc

#include "tron.hh"

int main(int argc, char **argv)
{
	Game* game = new TRON();
	game->Start();

	return 0;
}
