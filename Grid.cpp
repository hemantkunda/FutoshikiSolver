#include "Grid.h"

Grid::Grid(int **grid, int size) {
	layout = new QGridLayout(this);
	for (int r = 0; r < 2 * size - 1; r++) {
		for (int c = 0; c < 2 * size - 1; c++) {
			if (r % 2 == 0) {
				if (c % 2 == 0) {
					NumberButton *n = new NumberButton(grid[r] + c, size);
					numButtons.push_back(n);
					layout->addWidget(n, r, c, Qt::AlignCenter);
				}
				else {
					IneqButton *i = new IneqButton(grid[r] + c, true);
					ineqButtons.push_back(i);
					layout->addWidget(i, r, c, Qt::AlignCenter);
				}
			}
			else if (c % 2 == 0) {
				IneqButton *i = new IneqButton(grid[r] + c, false);
				ineqButtons.push_back(i);
				layout->addWidget(i, r, c, Qt::AlignCenter);
			}
		}
	}
	layout->setSpacing(15);
}

Grid::~Grid() {
	numButtons.clear();
	ineqButtons.clear();
	delete layout;
}

void Grid::reload() {
	for (unsigned i = 0; i < numButtons.size(); i++) {
		numButtons[i]->reload();
	}
	for (unsigned i = 0; i < ineqButtons.size(); i++) {
		ineqButtons[i]->reload();
	}
}