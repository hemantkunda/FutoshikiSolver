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

void IneqButton::toggle() {
	current = (current + 1) % 3;
	switch (current) {
		case 0:
			setIcon(QIcon(QPixap(empty)));
			*loc = empty;
			break;
		case 1:
			setIcon(QIcon(QPixap(lt)));
			*loc = lti;
			break;
		case 2:
			setIcon(QIcon(QPixap(gt)));
			*loc = gti;
			break;
	}
	setIconSize(QSize(25, 25));
}