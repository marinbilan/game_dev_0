#pragma once

#include "error.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>
#include "glew.h"
#include "glm/vec3.hpp"

namespace Common
{
	class Database
	{
	public:
		Database(Common::Error& err, const std::string& name);

		~Database();

		void preInit();
		void postInit();

		// Create Object (set0, set1, get0, get1)
		void create(const std::string& operation, const std::string& interface, std::vector<std::string>& arg0, std::vector<std::string>& arg1);
		// Set Member (set0, set1, get0)
		void setMember(const std::string& objName, const std::string& memberName, std::string& get0);

		// ----
		void getStringFromDB(const std::string& dbEntry, const std::string& dbTarget, std::string& dbParam);
		
		void getRest(const std::string& objName, const std::string& memberName, std::string& get0);

		// Get - vector of column strings
		void get(const std::string& set0, const std::string& set1, std::vector<std::string>& get0);
		// Get Rest - vector of column strings
		void getRest(const std::string& set0, const std::string& set1, std::vector<std::string>& get0);

		// ---- NEW ----
		void getColumnOfStrings12(const std::string& set0, std::vector<std::string>& get0, std::vector<std::string>& get1);

		void getColumnOfStrings22(const std::string& set0, const std::string& set1, std::vector<std::string>& get0, std::vector<std::string>& get1);

		void getFloat21(const std::string& set0, const std::string& set1, GLfloat& get0);

		void getVec3_21(const std::string& dbEntry, const std::string& dbTarget, glm::vec3& dbParam);

		void getColumn21(const std::string& set0, const std::string& set1, std::vector<std::string>& get0);


	    // ========================================================================================
        // NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION
        // ========================================================================================
		void getStringsFromDB(const std::string& dbPath, std::vector<std::string>& vectorOfStrings);

		void getFloat(const std::string& dbPath, GLfloat& getFloat);

		void getVec3(const std::string& dbPath, glm::vec3& vec3);

	private:
		std::string m_name;
	};
}