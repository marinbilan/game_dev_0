#include "database.h"


Common::Database::Database(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << "Database::Database::Database() constructor called!" << '\n';
}


Common::Database::~Database()
{
	std::cout << "Database::Database::~Database() destructor called!" << '\n';
}


void Common::Database::preInit()
{
	// std::cout << "Database::Database::preInit called!" << '\n';
}


void Common::Database::postInit()
{
	// std::cout << "Database::Database::postInit() called!" << '\n';
}


void Common::Database::getStringFromDB(const std::string& dbEntry, const std::string& dbTarget, std::string& dbParam)
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

void Common::Database::create(const std::string& operation, const std::string& interface, std::vector<std::string>& arg0, std::vector<std::string>& arg1)
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

void Common::Database::setMember(const std::string& objName, const std::string& memberName, std::string& get0)
{
	// dB File - m_name - database text file name
	std::ifstream dBFile(m_name);
	// dB Line
	std::string dBLine;
	// db Regex - dbEntry (name of the operation) dbTarget (Interface - class of objects with the same interface)
	std::regex regexLine(objName + "\\s+" + memberName + "\\s+(\\w+)");

	std::smatch match;
	while (std::getline(dBFile, dBLine))
	{
		if (std::regex_search(dBLine, match, regexLine))
		{
			get0 = match.str(1);
		}
	}
	/*
	if (!arg0.compare("")) // Raise error if no param in DB
	{
		// error = true;
	}
	*/
}


void Common::Database::getRest(const std::string& objName, const std::string& memberName, std::string& get0)
{
	// dB File - m_name - database text file name
	std::ifstream dBFile(m_name);
	// dB Line
	std::string dBLine;
	// db Regex - dbEntry (name of the operation) dbTarget (Interface - class of objects with the same interface)
	std::regex regexLine(objName + "\\s+" + memberName + "\\s+(.+)");

	std::smatch match;
	while (std::getline(dBFile, dBLine))
	{
		if (std::regex_search(dBLine, match, regexLine))
		{
			get0 = match.str(1);
		}
	}
	/*
	if (!arg0.compare("")) // Raise error if no param in DB
	{
		// error = true;
	}
	*/
}

void Common::Database::get(const std::string& set0, const std::string& set1, std::vector<std::string>& get0)
{
	// dB File - m_name - database text file name
	std::ifstream dBFile(m_name);
	// dB Line
	std::string dBLine;
	// db Regex - dbEntry (name of the operation) dbTarget (Interface - class of objects with the same interface)
	std::regex regexLine(set0 + "\\s+" + set1 + "\\s+(\\w+)");

	std::smatch match;
	while (std::getline(dBFile, dBLine))
	{
		if (std::regex_search(dBLine, match, regexLine))
		{
			// match.str(0) // Whole matched string
			// std::cout << " --------------- stringFromDb: " << match.str(1) << "\n";
			get0.push_back(match.str(1));
		}
	}
	/*
	if (!arg0.compare("")) // Raise error if no param in DB
	{
		// error = true;
	}
	*/
}


void Common::Database::getRest(const std::string& set0, const std::string& set1, std::vector<std::string>& get0)
{
	// dB File - m_name - database text file name
	std::ifstream dBFile(m_name);
	// dB Line
	std::string dBLine;
	// db Regex - dbEntry (name of the operation) dbTarget (Interface - class of objects with the same interface)
	std::regex regexLine(set0 + "\\s+" + set1 + "\\s+(.+)");

	std::smatch match;
	while (std::getline(dBFile, dBLine))
	{
		if (std::regex_search(dBLine, match, regexLine))
		{
			// match.str(0) // Whole matched string
			// std::cout << " --------------- stringFromDb: " << match.str(1) << "\n";
			get0.push_back(match.str(1));
		}
	}
	/*
	if (!arg0.compare("")) // Raise error if no param in DB
	{
		// error = true;
	}
	*/
}


void Common::Database::getColumnOfStrings12(const std::string& set0, std::vector<std::string>& get0, std::vector<std::string>& get1)
{
	// dB File - m_name - database text file name
	std::ifstream dBFile(m_name);
	// dB Line
	std::string dBLine;
	// db Regex - dbEntry (name of the operation) dbTarget (Interface - class of objects with the same interface)
	std::regex regexLine(set0 + "\\s+(\\w+)" + "\\s+(.+)");

	std::smatch match;
	while (std::getline(dBFile, dBLine))
	{
		if (std::regex_search(dBLine, match, regexLine))
		{
			get0.push_back(match.str(1)); // match.str(0) // Whole matched string
			get1.push_back(match.str(2)); // 
		}
	}
	/*
	if (!arg0.compare("")) // Raise error if no param in DB
	{
		// error = true;
	}
	*/
}


void Common::Database::getColumnOfStrings22(const std::string& set0, const std::string& set1, std::vector<std::string>& get0, std::vector<std::string>& get1)
{
	// dB File - m_name - database text file name
	std::ifstream dBFile(m_name);
	// dB Line
	std::string dBLine;
	// db Regex - dbEntry (name of the operation) dbTarget (Interface - class of objects with the same interface)
	std::regex regexLine(set0 + "\\s+" + set1 + "\\s+(\\w+)" + "\\s+(.+)");

	std::smatch match;
	while (std::getline(dBFile, dBLine))
	{
		if (std::regex_search(dBLine, match, regexLine))
		{
			get0.push_back(match.str(1)); // match.str(0) // Whole matched string
			get1.push_back(match.str(2)); // 
		}
	}
	/*
	if (!arg0.compare("")) // Raise error if no param in DB
	{
		// error = true;
	}
	*/
}


void Common::Database::getFloat21(const std::string& set0, const std::string& set1, GLfloat& get0)
{
	// dB File
	std::ifstream dBFile(m_name);
	// dB Line
	std::string dBLine;
	// db Regex
	std::regex regexLine(set0 + "\\s+" + set1 + "\\s+([-]?\\d+)(\\.\\d+)?");

	std::smatch match;
	while (std::getline(dBFile, dBLine))
	{
		if (std::regex_search(dBLine, match, regexLine))
		{
			get0 = std::stof(match.str(1) + match.str(2)); // match.str(0) // Whole matched string
		}
	}
}


void Common::Database::getVec3_21(const std::string& instanceName, const std::string& instanceMember, glm::vec3& dbParam)
{
	// dB File
	std::ifstream dBFile(m_name);
	// dB Line
	std::string dBLine;
	// dB Regex
	std::regex regexLine(instanceName + "\\s+" + instanceMember + "\\s+([-]?\\d+)(\\.\\d+)?\\s+([-]?\\d+)(\\.\\d+)?\\s+([-]?\\d+)(\\.\\d+)?");

	std::smatch match;
	while (std::getline(dBFile, dBLine))
	{
		if (std::regex_search(dBLine, match, regexLine))
		{
			dbParam = glm::vec3(std::stof(match.str(1) + match.str(2)),
				std::stof(match.str(3) + match.str(4)),
				std::stof(match.str(5) + match.str(6)));
		}
	}	
}


void Common::Database::getColumn21(const std::string& set0, const std::string& set1, std::vector<std::string>& get0)
{
	// dB File - m_name - database text file name
	std::ifstream dBFile(m_name);
	// dB Line
	std::string dBLine;
	std::regex regexLine(set0 + "\\s+" + set1 + "\\s+(\\w+)");

	std::smatch match;
	while (std::getline(dBFile, dBLine))
	{
		if (std::regex_search(dBLine, match, regexLine))
		{
			get0.push_back(match.str(1));
		}
	}
}


// ========================================================================================
// NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION
// ========================================================================================
void Common::Database::getStringsFromDB(const std::string& dbPath, std::vector<std::string>& vectorOfStrings)
{
	// dBFile - m_name: database text file name
	std::ifstream dBFile(m_name);
	// dB Line: each line in dBFile
	std::string dBLine;
	// DB ex:
	//                   dbPath                       "\\s+(.+)"
	//                   models             string     staticModel dynamicModels  otherModels
	std::regex regexLine("^" + dbPath + "\\s+" + "string" + "\\s+(.+)");

	std::smatch match;
	std::string wantedString;
	
	while (std::getline(dBFile, dBLine))
	{
		if (std::regex_search(dBLine, match, regexLine))
		{
			wantedString = match.str(1); // match.str(0) - Whole matched string
		}
	}

	// wantedString: "staticModel dynamicModels  otherModels"
	std::istringstream stringOfElements(wantedString);

	// separate wantedString "staticModel dynamicModels  otherModels" in tokens (vector of strings)
	std::vector<std::string> vectorOfLocalStrings((std::istream_iterator<std::string>(stringOfElements)),
		std::istream_iterator<std::string>());

	vectorOfStrings = vectorOfLocalStrings;

	if (!wantedString.compare("")) // Raise error if no param in DB
	{
		std::string falseStr("false");
		vectorOfStrings.push_back(falseStr);
	}
}


void Common::Database::getFloat(const std::string& dbPath, GLfloat& getFloat)
{
	// dB File
	std::ifstream dBFile(m_name);
	// dB Line
	std::string dBLine;
	// db Regex
	std::regex regexLine(dbPath + "\\s+" + "float" + "\\s+([-]?\\d+)(\\.\\d+)?");

	std::smatch match;
	while (std::getline(dBFile, dBLine))
	{
		if (std::regex_search(dBLine, match, regexLine))
		{
			getFloat = std::stof(match.str(1) + match.str(2)); // match.str(0) // Whole matched string
		}
	}
}


void Common::Database::getVec3(const std::string& dbPath, glm::vec3& vec3)
{
	// dB File
	std::ifstream dBFile(m_name);
	// dB Line
	std::string dBLine;
	// dB Regex
	std::regex regexLine(dbPath + "\\s+" + "vec3" + "\\s+([-]?\\d+)(\\.\\d+)?\\s+([-]?\\d+)(\\.\\d+)?\\s+([-]?\\d+)(\\.\\d+)?");

	std::smatch match;
	while (std::getline(dBFile, dBLine))
	{
		if (std::regex_search(dBLine, match, regexLine))
		{
			vec3 = glm::vec3(std::stof(match.str(1) + match.str(2)), // match.str(0) - whole string
				std::stof(match.str(3) + match.str(4)),
				std::stof(match.str(5) + match.str(6)));
		}
	}
}