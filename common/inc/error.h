#pragma once
#include <string>
#include <iostream>
#include <vector>


namespace Common
{
class Error
{
public:
	void setError(const std::string& arg0);

	void printErrors();

private:
std::vector<std::string> m_errors;
};
} // End of namespace