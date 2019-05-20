#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>


#define LOG __DATE__, __TIME__, __FILENAME__, __LINE__,
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)


namespace Common
{
	class Log
	{
	public:
		Log(const std::string& name) : m_name(name) 
		{
			std::ofstream m_logFile("logFile.txt");
		}

		void LOGFILE(const char* date, const char* time, const char* file, int line, std::string msg);

		void INFOCMD(const char* date, const char* time, const char* file, int line, std::string msg);

	private:

		std::string m_name;

		std::ofstream m_logFile;
	};

}