#ifndef NUMBER_BUTTON_H_
#define NUMBER_BUTTON_H_

#include <QPushButton>
#include <QString>
#include <QSize>

class NumberButton : public QPushButton {
	Q_OBJECT;
public:
	NumberButton(int *loc, int size);
	~NumberButton();

public slots:
	void increment();

private:
	int size;
	int *loc;
}

#endif
