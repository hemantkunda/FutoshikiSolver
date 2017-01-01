#include "SolverUI.h"

SolverUI::SolverUI() {
	buttonStyle = QString("background-color: red; color: white; ");
	backgroundStyle = QString("background-color: white; ");
	labelStyle = QString("color: red");
	comboboxStyle = buttonStyle + QString("margin: 0; selection-color: yellow; ");
	buildUI(4, true);
}

SolverUI::~SolverUI() {
	delete solveButton;
	delete clearButton;
	delete title;
	delete sizes;
	delete settings;
	delete grid;
	delete layout;
	for (int i = 0; i < 2 * size - 1; i++) {
		delete [] board[i];
	}
	delete [] board;
}

std::string SolverUI::exportPuzzle() {
	QInputDialog *dialog = new QInputDialog();
	dialog->setInputMode(QInputDialog::TextInput);
	dialog->setCancelButtonText(QString("Cancel"));
	dialog->setOkButtonText(QString("Confirm"));
	dialog->setLabelText(QString("Name this puzzle:"));
	std::string filename = "";
	if (dialog->exec()) {
		std::string name = dialog->textValue().toStdString();
		if (name.size() == 0) {
			time_t currTime = time(0);
			struct tm *timeinfo = localtime(&currTime);
			char time[80];
			strftime(time, sizeof(time), "%d/%m/%Y %H-%M-%S", timeinfo);
			name = std::string(time);
		}
		filename = "puzzle_" + name;
		Util::writefile(filename + ".in", board, size);
	}
	delete dialog;
	return filename;
}

void SolverUI::clear() {
	for (int i = 0; i < 2 * size - 1; i++) {
		for (int j = 0; j < 2 * size - 1; j++) {
			board[i][j] = 0;
		}
	}
	grid->reload();
}

void SolverUI::load() {
	QString fileName = QFileDialog::getOpenFileName(this, QString("Open..."), ".");
	if (Util::verify(fileName.toStdString(), size)) {
		readfile(fileName.toStdString());
	}
	else {
		QMessageBox *message = new QMessageBox();
		message->setStandardButtons(QMessageBox::Ok);
		message->button(QMessageBox::Ok)->setStyleSheet("background-color: red; color: white;");
		message->setWindowTitle(QString("Error"));
		message->setText(QString("Error - Invalid file format."));
		message->setStyleSheet("color: red;");
		message->exec();
		delete message;
	}
}

void SolverUI::solve() {
	std::string filename = exportPuzzle();
	if (filename.size() == 0) {
		return;
	}
	Solver s(size, filename + ".in", filename + ".out");
	s.solve();
	s.output();
	std::ifstream in(filename + ".out");
	std::string line;
	std::getline(in, line);
	if (line[0] == 'N') {
		QMessageBox *message = new QMessageBox();
		message->setStandardButtons(QMessageBox::Ok);
		message->button(QMessageBox::Ok)->setStyleSheet("background-color: red; color: white;");
		message->setWindowTitle(QString("Alert"));
		message->setText(QString("The inputted puzzle has no solution."));
		message->exec();
		delete message;
		return;
	}
	in.close();
	readfile(filename + ".out");
}

void SolverUI::readfile(std::string filename) {
	std::ifstream in(filename);
	std::string line;
	std::getline(in, line);
	std::stringstream ss(line);
	int newSize;
	ss >> newSize;
	if (size != newSize) {
		buildUI(newSize, false);
		sizes->blockSignals(true);
		sizes->setCurrentIndex(newSize - 4);
		sizes->blockSignals(false);
	}
	in.close();
	Util::readfile(filename, board, size);
	grid->reload();
}

void SolverUI::toggleSize(int index) {
	buildUI(index + 4, false);
}

void SolverUI::buildUI(int size, bool init) {
	// delete old
	if (!init) {
		delete solveButton;
		delete clearButton;
		delete loadButton;
		delete title;
		delete settings;
		delete grid;
		delete layout;
		for (int i = 0; i < 2 * this->size - 1; i++) {
			delete [] board[i];
		}
		delete [] board;
	}
	// recreate
	this->size = size;
	this->layout = new QHBoxLayout(this);
	layout->setSizeConstraint(QLayout::SetFixedSize);
	this->board = new int*[2 * size - 1];
	for (int i = 0; i < 2 * size - 1; i++) {
		board[i] = new int[2 * size - 1];
		for (int j = 0; j < 2 * size - 1; j++) {
			board[i][j] = 0;
		}
	}
	this->grid = new Grid(board, size);
	this->settings = new QVBoxLayout();
	layout->addWidget(grid);
	layout->addLayout(settings);

	title = new QLabel();
	title->setText(QString("Futoshiki Solver"));
	title->setStyleSheet(labelStyle);
	settings->addWidget(title);

	if (init) {
		sizes = new QComboBox();
		sizes->addItem(QString("4x4"));
		sizes->addItem(QString("5x5"));
		sizes->addItem(QString("6x6"));
		sizes->addItem(QString("7x7"));
		sizes->addItem(QString("8x8"));
		sizes->addItem(QString("9x9"));
		sizes->setStyleSheet(comboboxStyle);
		connect(sizes, SIGNAL(currentIndexChanged(int)), this, SLOT(toggleSize(int)));
	}
	settings->addWidget(sizes);

	solveButton = new QPushButton();
	solveButton->setText(QString("Solve"));
	solveButton->setStyleSheet(buttonStyle);
	connect(solveButton, SIGNAL(clicked()), this, SLOT(solve()));
	settings->addWidget(solveButton);

	loadButton = new QPushButton();
	loadButton->setText(QString("Load"));
	loadButton->setStyleSheet(buttonStyle);
	connect(loadButton, SIGNAL(clicked()), this, SLOT(load()));
	settings->addWidget(loadButton);

	clearButton = new QPushButton();
	clearButton->setText(QString("Clear"));
	clearButton->setStyleSheet(buttonStyle);
	connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
	settings->addWidget(clearButton);

	setLayout(layout);
	setStyleSheet(backgroundStyle);
	this->setWindowTitle(QString("Futoshiki Solver"));
	this->show();
}

