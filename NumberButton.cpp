#include "NumberButton.h"

NumberButton::NumberButton(int *loc, int size) {
	this->size = size;
	this->loc = loc;
	connect(this, SIGNAL(clicked()), this, SLOT(increment()));
	setText(QString(""));
	setFixedSize(QSize(75, 75));
}

NumberButton::~NumberButton() {

}

void NumberButton::increment() {
	*loc = (*loc + 1) % (size + 1);
	if (*loc != 0) {
		setText(QString::number(*loc));
	}
	else {
		setText(QString(""));
	}
}