#ifndef GRID_H_
#define GRID_H_

#include <QWidget>
#include <QString>
#include <QGridLayout>

#include <vector>

class Grid : public QWidget {
	Q_OBJECT;
public:
	Grid(int **grid, int size);
	~Grid();

private:
	QGridLayout *layout;
	std::vector<NumberButton*> numButtons;
	std::vector<IneqButton*> ineqButtons;
}

#endif