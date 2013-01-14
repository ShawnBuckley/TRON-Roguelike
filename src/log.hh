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
	bool Open(std::string _file);
	void Write(std::string _string);
	void Close();
};

#endif // TRON_RLENGINEX_LOG_HH
