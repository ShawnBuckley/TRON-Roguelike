// TRON-Roguelike log.hh

#ifndef __INCLUDE_LOG_HH__
#define __INCLUDE_LOG_HH__

#include <string>
#include <fstream>

bool OpenLog(std::string _file);
void CloseLog(std::string _file);

extern std::ofstream log_file;

#endif // __INCLUDE_LOG_HH__
