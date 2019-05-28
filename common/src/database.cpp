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
	std::cout << "Database::Database::preInit called!" << '\n';
}


void Common::Database::postInit()
{
	std::cout << "Database::Database::postInit() called!" << '\n';
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