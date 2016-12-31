#include "SolverUI.h"

SolverUI::SolverUI() {
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
		char *conv = new char[5] {' ', '<', '>', '^', 'v'};
		filename = "puzzle_" + name;
		std::ofstream out(filename + ".in");
		for (int i = 0; i < 2 * size - 1; i++) {
			for (int j = 0; j < 2 * size - 1; j++) {
				if (i % 2 == 0 && j % 2 == 0) {
					out << board[i][j];
				}
				else {
					out << conv[board[i][j]];
				}
			}
			out << "\n";
		}
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
	readfile(fileName.toStdString());
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
		message->setText("The inputted puzzle has no solution.");
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
	for (int i = 0; i < 2 * size - 1; i++) {
		std::getline(in, line);
		if (i % 2 == 0) {
			for (int j = 0; j < 2 * size - 1; j++) {
				if (j % 2 == 0) {
					if (line[j] != ' ') {
						board[i][j] = (int)(line[j] - '0');
					}
					else {
						board[i][j] = 0;
					}
				}
				else {
					if (line[j] == ' ') {
						board[i][j] = 0;
					}
					if (line[j] == '<') {
						board[i][j] = 1;
					}
					if (line[j] == '>') {
						board[i][j] = 2;
					}
					if (line[j] == '^') {
						board[i][j] = 3;
					}
					if (line[j] == 'v') {
						board[i][j] = 4;
					}
				}
			}
		}
		else {
			for (int j = 0; j < 2 * size - 1; j++) {
				if (j % 2 == 0) {
					if (line[j] == ' ') {
						board[i][j] = 0;
					}
					if (line[j] == '<') {
						board[i][j] = 1;
					}
					if (line[j] == '>') {
						board[i][j] = 2;
					}
					if (line[j] == '^') {
						board[i][j] = 3;
					}
					if (line[j] == 'v') {
						board[i][j] = 4;
					}
				}
				else {
					board[i][j] = 0;
				}
			}
		}
	}
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
	settings->addWidget(title);

	if (init) {
		sizes = new QComboBox();
		sizes->addItem(QString("4x4"));
		sizes->addItem(QString("5x5"));
		sizes->addItem(QString("6x6"));
		sizes->addItem(QString("7x7"));
		sizes->addItem(QString("8x8"));
		sizes->addItem(QString("9x9"));
		connect(sizes, SIGNAL(currentIndexChanged(int)), this, SLOT(toggleSize(int)));
	}
	settings->addWidget(sizes);

	solveButton = new QPushButton();
	solveButton->setText(QString("Solve"));
	connect(solveButton, SIGNAL(clicked()), this, SLOT(solve()));
	settings->addWidget(solveButton);

	loadButton = new QPushButton();
	loadButton->setText(QString("Load"));
	connect(loadButton, SIGNAL(clicked()), this, SLOT(load()));
	settings->addWidget(loadButton);

	clearButton = new QPushButton();
	clearButton->setText(QString("Clear"));
	connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
	settings->addWidget(clearButton);

	setLayout(layout);
	this->setWindowTitle(QString("Futoshiki Solver"));
	this->show();
}

