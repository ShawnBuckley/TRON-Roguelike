// TRON-Roguelike log.cc

#include "log.hh"

Log::Log(std::string _file)
{
	file_.open(_file.c_str());
}

Log::~Log()
{
	file_.close();
}

void Log::Write(std::string _string)
{
	file_ << _string;
}
