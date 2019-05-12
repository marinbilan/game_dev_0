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

