#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Solver {
public: 
	
	// constructor - uses inFile/size to read in the board and saves outFile
	// to output the solution later
	Solver(unsigned size, std::string inFile, std::string outFile);

	// deletes all memory allocated to the Solver object
	~Solver();

	// returns true if there is a solution, false otherwise
	// stores the solution if it exists
	bool solve();

	// outputs the found solution to the output file specified in the constructor
	void output();

private:

	// constructs all possible values for the location at the specified row (r)
	// and column (c) by considering existing values in that same row/column as
	// well as any inequalities that must be satisfied by this location and the
	// ones above/to the left.
	int* constructCandidates(int r, int c);

	// tries all possible values at the specified row/col and repeats with the
	// next location in line - starts at the first row and processes each row
	// from left to right. a solution is found if the algorithm runs out of 
	// locations (i.e. r == 2 * size + 1).
	void backtrack(int r, int c);

	// reads in the starting problem from the specified file, considering only
	// the first (2 * size - 1) characters of the first (2 * size - 1) lines.
	void readfile(unsigned size, std::string filename);

	// deep copies the current grid to another 2d array (this new array is used
	// in the output method)
	void saveSolution();

public:

	unsigned size;
	bool solved;
	int **grid;
	int **solution;
	std::string outFile;
};

