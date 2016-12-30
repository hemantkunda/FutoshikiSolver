#include "IneqButton.h"

IneqButton::IneqButton(int *loc, bool horizontal) {
	if (horizontal) {
		this->lt = "images/hlt.png";
		this->gt = "images/hgt.png";
		this->lti = 1;
		this->gti = 2;
	}
	else {
		this->lt = "images/vlt.png";
		this->gt = "images/vgt.png";
		this->lti = 3;
		this->gti = 4;
	}
	this->empty = "images/empty.png";
	this->emptyI = 0;
	this->current = 0;
	this->loc = loc;
	connect(this, SIGNAL(clicked()), this, SLOT(toggle()));
	this->setFixedSize(QSize(35, 35));
}

IneqButton::~IneqButton() {

}

void IneqButton::reload() {
	if (*loc == emptyI) {
		setIcon(QIcon(QPixmap(QString(empty.c_str()))));
		current = 0;
	}
	else if (*loc == lti) {
		setIcon(QIcon(QPixmap(QString(lt.c_str()))));
		current = 1;
	}
	else if (*loc == gti) { 
		setIcon(QIcon(QPixmap(QString(gt.c_str()))));
		current = 2;
	}
}

void IneqButton::toggle() {
	current = (current + 1) % 3;
	switch (current) {
		case 0:
			setIcon(QIcon(QPixmap(QString(empty.c_str()))));
			*loc = emptyI;
			break;
		case 1:
			setIcon(QIcon(QPixmap(QString(lt.c_str()))));
			*loc = lti;
			break;
		case 2:
			setIcon(QIcon(QPixmap(QString(gt.c_str()))));
			*loc = gti;
			break;
	}
	setIconSize(QSize(25, 25));
}