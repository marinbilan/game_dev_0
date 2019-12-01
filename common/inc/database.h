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


		void getStringsFromDB(const std::string& dbPath, std::vector<std::string>& vectorOfStrings);

		void getFloat(const std::string& dbPath, GLfloat& getFloat);

		void getVec3(const std::string& dbPath, glm::vec3& vec3);

	private:
		std::string m_name;
	};
}