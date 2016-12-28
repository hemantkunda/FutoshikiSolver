#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Solver {
public: 
	
	Solver(unsigned size, std::string inFile, std::string outFile);
	~Solver();
	bool solve();
	int* constructCandidates(int r, int c);
	void backtrack(int r, int c);
	void readfile(unsigned size, std::string filename);
	void saveSolution();
	void output();

public:
	unsigned size;
	bool solved;
	int **grid;
	int **solution;
	std::string outFile;
};

