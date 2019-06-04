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

		// Create Object (set0, set1, get0, get1)
		void create(const std::string& operation, const std::string& interface, std::vector<std::string>& arg0, std::vector<std::string>& arg1);
		// Set Member (set0, set1, get0)
		void setMember(const std::string& objName, const std::string& memberName, std::string& get0);

		void getRest(const std::string& objName, const std::string& memberName, std::string& get0);

		// Get - vector of column strings
		void get(const std::string& set0, const std::string& set1, std::vector<std::string>& get0);
		// Get Rest - vector of column strings
		void getRest(const std::string& set0, const std::string& set1, std::vector<std::string>& get0);

	private:
		std::string m_name;
	};
}