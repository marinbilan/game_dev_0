#pragma once

#include "error.h"

#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>


namespace Common
{
	class Database
	{
	public:
		Database(Common::Error& err, const std::string& name);

		~Database();

		void preInit();
		void postInit();

		void getStringFromDB(const std::string& dbEntry, const std::string& dbTarget, std::string& dbParam);

		void create(const std::string& operation, const std::string& interface, std::vector<std::string>& arg0, std::vector<std::string>& arg1);

	private:
		std::string m_name;
	};
}