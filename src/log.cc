// TRON-Roguelike log.cc

#include <fstream>

#include "log.hh"

std::ofstream log_file;

bool OpenLog(std::string _file)
{
	log_file.open(_file.c_str());

	return log_file.good();
}

void CloseLog(std::string _file)
{
	log_file.close();
}
