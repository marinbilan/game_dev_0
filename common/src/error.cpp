#include "error.h"


void Common::Error::setError(const std::string& arg0)
{
	m_errors.push_back(arg0);
}


void Common::Error::printErrors()
{
	for (auto it : m_errors)
	{
		std::cout << it << '\n';
	}
}