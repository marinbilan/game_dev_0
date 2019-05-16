#pragma once
#include <string>
#include <iostream>
#include <vector>


namespace Common
{

class Error
{
public:
	// Error(const std::string& name) : m_name(name) {}

	void setError(const std::string& arg0);

	void printErrors();

private:
std::string m_name;
std::vector<std::string> m_errors;
};

}