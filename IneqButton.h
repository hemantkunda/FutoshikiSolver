#ifndef INEQ_BUTTON_H_
#define INEQ_BUTTON_H_

#include <QPushButton>
#include <QString>
#include <QIcon>
#include <QSize>
#include <QPixmap>
#include <string>

class IneqButton : public QPushButton {
	Q_OBJECT;
public:
	IneqButton(int *loc, bool horizontal);
	~IneqButton();

public slots:
	void toggle();

private:
	std::string empty;
	std::string lt;
	std::string gt;
	int emptyI;
	int lti;
	int gti;
	int current;
	int *loc;
};

#endif