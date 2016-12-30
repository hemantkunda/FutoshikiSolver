#ifndef GRID_H_
#define GRID_H_

#include <QWidget>
#include <QString>
#include <QGridLayout>

#include <vector>

#include "NumberButton.h"
#include "IneqButton.h"

class Grid : public QWidget {
	Q_OBJECT;
public:
	Grid(int **grid, int size);
	~Grid();
	void reload();
private:
	QGridLayout *layout;
	std::vector<NumberButton*> numButtons;
	std::vector<IneqButton*> ineqButtons;
};

#endif