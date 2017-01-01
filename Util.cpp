#include "Util.h"

void Util::readfile(std::string filename, int **array, int size) {
	std::ifstream in(filename);
	std::string line;
	std::getline(in, line);
	for (int i = 0; i < 2 * size - 1; i++) {
		std::getline(in, line);
		if (i % 2 == 0) {
			for (int j = 0; j < 2 * size - 1; j++) {
				if (j % 2 == 0) {
					if (line[j] != ' ') {
						array[i][j] = (int)(line[j] - '0');
					}
					else {
						array[i][j] = 0;
					}
				}
				else {
					if (line[j] == ' ') {
						array[i][j] = 0;
					}
					if (line[j] == '<') {
						array[i][j] = 1;
					}
					if (line[j] == '>') {
						array[i][j] = 2;
					}
					if (line[j] == '^') {
						array[i][j] = 3;
					}
					if (line[j] == 'v') {
						array[i][j] = 4;
					}
				}
			}
		}
		else {
			for (int j = 0; j < 2 * size - 1; j++) {
				if (j % 2 == 0) {
					if (line[j] == ' ') {
						array[i][j] = 0;
					}
					if (line[j] == '<') {
						array[i][j] = 1;
					}
					if (line[j] == '>') {
						array[i][j] = 2;
					}
					if (line[j] == '^') {
						array[i][j] = 3;
					}
					if (line[j] == 'v') {
						array[i][j] = 4;
					}
				}
				else {
					array[i][j] = 0;
				}
			}
		}
	}
}

void Util::writefile(std::string filename, int **array, int size) {
	std::ofstream out(filename);
	out << size << "\n";
	char *conv = new char[5] {' ', '<', '>', '^', 'v'};
	for (int i = 0; i < 2 * size - 1; i++) {
		for (int j = 0; j < 2 * size - 1; j++) {
			if (i % 2 == 0 && j % 2 == 0) {
				out << array[i][j];
			}
			else {
				out << conv[array[i][j]];
			}
		}
		out << "\n";
	}
}