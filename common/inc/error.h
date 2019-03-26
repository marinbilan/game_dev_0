#pragma once
#include <string>
#include <iostream>

namespace Common
{

class Error
{
public:
	void setError(const std::string& arg0)
	{
		m_error = arg0;
	}

	void printError()
	{
		std::cout << m_error << std::endl;
	}

private:
std::string m_error;
};

}