#ifndef SOLVER_UI_H
#define SOLVER_UI_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QInputDialog>
#include <QSize>
#include <QBrush>
#include <QColor>
#include <QString>
#include <QComboBox>
#include <QStringList>

#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <sstream>

#include "solver.h"
#include "Grid.h"

class SolverUI : public QWidget {
	Q_OBJECT

public:
	SolverUI();
	~SolverUI();

public slots:
	void solve();
	void clear();
	void toggleSize(int index);

private:
	std::string exportPuzzle();
	void buildUI(int size, bool init);

private:
	Grid *grid;
	QVBoxLayout *settings;
	QHBoxLayout *layout;
	QLabel *title;
	QComboBox *sizes;
	QPushButton *solveButton;
	QPushButton *clearButton;

	int **board;
	int size;
};

#endif