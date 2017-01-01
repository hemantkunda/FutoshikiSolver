#include "solver.h"

Solver::Solver(unsigned size, std::string inFile, std::string outFile) {
	this->size = size;
	this->solved = false;
	this->outFile = outFile;
	this->grid = new int*[2 * size - 1];
	this->constant = new bool*[2 * size - 1];
	for (unsigned i = 0; i < 2 * size - 1; i++) {
		grid[i] = new int[2 * size - 1];
		constant[i] = new bool[2 * size - 1];
	}
	readfile(size, inFile);
}

Solver::~Solver() {
	for (unsigned i = 0; i < 2 * size - 1; i++) {
		delete [] grid[i];
		delete [] constant[i];
	}
	delete [] constant;
	delete [] grid;
	if (solved) {
		for (unsigned i = 0; i < 2 * size - 1; i++) {
			delete [] solution[i];
		}
		delete [] solution;
	}
}

bool Solver::solve() {
	backtrack(0, 0);
	return solved;
}

void Solver::backtrack(int r, int c) {
	if ((unsigned)r >= 2 * size) {
		solved = true;
		saveSolution();
		return;
	}
	int nextR = r;
	int nextC = c + 2;
	if ((unsigned)nextC >= 2 * size) {
		nextC = 0;
		nextR = r + 2;
	}
	if (constant[r][c]) {
		backtrack(nextR, nextC);
	}
	else {
		unsigned *cand = constructCandidates(r, c);
		for (unsigned i = 1; i < size + 1; i++) {
			if (cand[i] == 0) {
				continue;
			}
			grid[r][c] = cand[i];
			backtrack(nextR, nextC);
			grid[r][c] = 0;
		}
		delete [] cand;
	}
}

void Solver::saveSolution() {
	solution = new int*[2 * size - 1];
	for (unsigned i = 0; i < 2 * size - 1; i++) {
		solution[i] = new int[2 * size - 1];
		for (unsigned j = 0; j < 2 * size - 1; j++) {
			solution[i][j] = grid[i][j];
		}
	}
}

unsigned* Solver::constructCandidates(int r, int c) {
	unsigned *cand = new unsigned[size + 1];
	for (unsigned i = 1; i <= size; i++) {
		cand[i] = i;
	}
	for (unsigned i = 0; i < 2 * size - 1; i += 2) {
		if (i != (unsigned)c) {
			cand[grid[r][i]] = 0;
		}
		if (i != (unsigned)r) {
			cand[grid[i][c]] = 0;
		}
	}
	//examine this location's relationship to neighboring ones
	// above
	if (r - 1 >= 0) {
		unsigned ineqA = grid[r - 1][c], above = grid[r - 2][c];
		switch (ineqA) {
			case 3:
				for (unsigned i = 1; i <= above; i++) {
					cand[i] = 0;
				}
				break;
			case 4:
				for (unsigned i = above; i <= size; i++) {
					cand[i] = 0;
				}
				break;
			default:
				break;
		}
	}
	// left
	if (c - 1 >= 0) {
		unsigned ineqL = grid[r][c - 1], left = grid[r][c - 2];
		switch (ineqL) {
			case 1:
				for (unsigned i = 1; i <= left; i++) {
					cand[i] = 0;
				}
				break;
			case 2:
				for (unsigned i = left; i <= size; i++) {
					cand[i] = 0;
				}
				break;
			default:
				break;
		}
	}
	// right
	if ((unsigned)(c + 1) < 2 * size - 1) {
		unsigned ineqR = grid[r][c + 1], right = grid[r][c + 2];
		if (right != 0) {
			switch (ineqR) {
				case 1:
					for (unsigned i = right; i <= size; i++) {
						cand[i] = 0;
					}
					break;
				case 2:
					for (unsigned i = 1; i <= right; i++) {
						cand[i] = 0;
					}
					break;
				default:
					break;
			}
		}
	}
	// below
	if ((unsigned)(r + 1) < 2 * size - 1) {
		unsigned ineqT = grid[r + 1][c], below = grid[r + 2][c];
		if (below != 0) {
			switch (ineqT) {
				case 3:
					for (unsigned i = below; i <= size; i++) {
						cand[i] = 0;
					}
					break;
				case 4:
					for (unsigned i = 1; i <= below; i++) {
						cand[i] = 0;
					}
					break;
				default:
					break;
			}
		}
	}
	return cand;
}

void Solver::readfile(unsigned size, std::string filename) {
	Util::readfile(filename, grid, size);
	for (unsigned r = 0; r < 2 * size - 1; r++) {
		for (unsigned c = 0; c < 2 * size - 1; c++) {
			constant[r][c] = (grid[r][c] != 0);
		}
	}
}

void Solver::output() {
	if (!solved) {
		std::ofstream out(outFile);
		out << "No solution\n";
		out.close();
		return;
	}
	Util::writefile(outFile, solution, size);
}




