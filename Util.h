#ifndef UTIL_H_
#define UTIL_H_

#include <fstream>
#include <sstream>
#include <string>

class Util {
public:
	static bool verify(std::string filename, int size);
	static void readfile(std::string filename, int **array, int size);
	static void writefile(std::string filename, int **array, int size);
};

#endif
