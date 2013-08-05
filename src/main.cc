// TRON-Roguelike Main.cc

#include <yaml-cpp/yaml.h>

#include "tron.hh"

int main(int argc, char **argv)
{
	if(argc > 1)
	{
		YAML::Node in = YAML::LoadFile(argv[1]);
		Game* game = new TRON(in);
	}
	else
	{
		printf("else");
		Game* game = new TRON();
		game->Start();
	}

	return 0;
}
