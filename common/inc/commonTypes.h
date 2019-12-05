#pragma once

// Factory stuff
#define FACTORY Common::Factory::getInstance()

// DB stuff
// #define DB      Common::Factory::getInstance() // .getDatabase() // ->get

// Log stuff
#define LOG __DATE__, __TIME__, __FILENAME__, __LINE__,
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)