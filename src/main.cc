// TRON-Roguelike Main.cc

#include <yaml-cpp/yaml.h>

#include "tron.hh"
#include "tronserializer.hh"

int main(int argc, char **argv)
{
	if(argc > 1)
	{
		YAML::Node in = YAML::LoadFile(argv[1]);
		TronSerializer tron_serializer;
		Game* game = tron_serializer.UnserializeTRON(in);
		game->Run();
	}
	else
	{
		printf("else");
		Game* game = new TRON();
		game->Start();
	}

	return 0;
}
