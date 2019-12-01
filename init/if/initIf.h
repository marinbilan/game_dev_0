#pragma once
#include <string>


namespace Init
{
class InitIf
{
public:
	~InitIf()
	{
	}

	// TODO: getName

	virtual void preInit() {};
	virtual void postInit() {};

};
}