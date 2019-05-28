#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>


namespace Common
{
	class Log
	{
	public:
		Log(const std::string& name) : m_name(name), m_logFile("_log/logFile.txt")
		{

		}

		void LOGFILE(const char* date, const char* time, const char* file, int line, const std::string& msg);

		void INFOCMD(const char* date, const char* time, const char* file, int line, const std::string& msg);

	private:

		std::string m_name;

		std::ofstream m_logFile;
	};

}