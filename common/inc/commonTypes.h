#pragma once

// Factory stuff
#define FACTORY Common::Factory::getInstance()

// Log stuff
#define LOG __DATE__, __TIME__, __FILENAME__, __LINE__,
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)