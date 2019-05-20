#include "log.h"


void Common::Log::LOGFILE(const char* date, const char* time, const char* file, int line, std::string msg)
{
	m_logFile << "[ " << date << " " << time << " ]" << " { FILENAME: " << file << " }" << " { LINE: " << line << " }" << " { INFO: " << msg << " }" << std::endl;
}


void Common::Log::INFOCMD(const char* date, const char* time, const char* file, int line, std::string msg)
{
	std::cout << "[ " << date << " " << time << " ]" << " { FILENAME: " << file << " }" << " { LINE: " << line << " }" << " { INFO: " << msg << " }" << std::endl;
}