// TRON-Roguelike log.cc

#include "log.hh"

bool Log::Open(std::string _file)
{
	file_.open(_file.c_str());

	return file_.good();
}

void Log::Write(std::string _string)
{
	file_ << _string;
}

void Log::Close()
{
	file_.close();
}
