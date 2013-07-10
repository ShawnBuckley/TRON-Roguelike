// TRON-Roguelike log.hh

#ifndef TRON_RLENGINEX_LOG_HH
#define TRON_RLENGINEX_LOG_HH

#include <string>
#include <fstream>

class Log
{
  private:
	std::ofstream file_;

  public:
	Log(std::string _file);
	~Log();
	void Write(std::string _string);
};

#endif // TRON_RLENGINEX_LOG_HH
