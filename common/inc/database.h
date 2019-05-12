#pragma once

#include "error.h"

#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
// #include <memory>

namespace Common
{
	class Database
	{
	public:
		Database(Common::Error& err, const std::string& name);

		~Database();

		void preInit();
		void postInit();

		void getStringFromDB(const std::string& dbEntry, const std::string& dbTarget, std::string& dbParam)
		{
			// dB File - m_name - database text file name
			std::ifstream dBFile(m_name);
			// dB Line
			std::string dBLine;
			// db Regex - dbEntry (name of the operation) dbTarget (Interface - class of objects with the same interface)
			std::regex regexLine(dbEntry + "\\s+" + dbTarget + "\\s+(\\w+)");

			std::smatch match;
			while (std::getline(dBFile, dBLine))
			{
				if (std::regex_search(dBLine, match, regexLine))
				{
					dbParam = match.str(1); // match.str(0) // Whole matched string
				}
			}

			if (!dbParam.compare("")) // Raise error if no param in DB
			{
				// error = true;
			}
		}

		void create(const std::string& operation, const std::string& interface, std::vector<std::string>& arg0, std::vector<std::string>& arg1)
		{
			// dB File - m_name - database text file name
			std::ifstream dBFile(m_name);
			// dB Line
			std::string dBLine;
			// db Regex - dbEntry (name of the operation) dbTarget (Interface - class of objects with the same interface)
			std::regex regexLine(operation + "\\s+" + interface + "\\s+(\\w+)" + "\\s+(\\w+)");

			std::smatch match;
			while (std::getline(dBFile, dBLine))
			{
				if (std::regex_search(dBLine, match, regexLine))
				{
					arg0.push_back(match.str(1)); // match.str(0) // Whole matched string
					arg1.push_back(match.str(2)); // 
				}
			}
			/*
			if (!arg0.compare("")) // Raise error if no param in DB
			{
				// error = true;
			}
			*/
		}

	private:
		std::string m_name;
	};
}