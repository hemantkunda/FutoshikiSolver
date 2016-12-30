#include "NumberButton.h"

NumberButton::NumberButton(int *loc, int size) {
	this->size = size;
	this->loc = loc;
	connect(this, SIGNAL(clicked()), this, SLOT(increment()));
	setText(QString(""));
	QFont font;
	font.setPointSize(25);
	setFont(font);
	setFixedSize(QSize(55, 55));
}

NumberButton::~NumberButton() {

}

void NumberButton::reload() {
	int newVal = *loc;
	if (newVal != 0) {
		setText(QString::number(newVal));
	}
	else {
		setText(QString(""));
	}
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
