#pragma once
#include <string>

//#include "controlIf.h"
//#include "controlDefault.h"


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