#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include <QMenuBar>
#include <QAction>
#include <QFontDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

class MyMainWindow : public QMainWindow {
public:
    MyMainWindow();

private:
    QLabel* timeLabel;
    QTimer* timer;

    QFont currentFont;
    QColor currentColor;

    void updateTime();
    void changeAppearance();
    void saveToFile();
    void loadFromFile();
};

MyMainWindow::MyMainWindow() {
    timeLabel = new QLabel(this);
    timeLabel->move(20, 40);

    currentFont = QFont("Arial", 24);
    currentColor = Qt::black;

    timeLabel->setFont(currentFont);
    timeLabel->setStyleSheet("color: black");

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MyMainWindow::updateTime);
    timer->start(1000);

    updateTime();

    QMenu* fileMenu = menuBar()->addMenu("File");
    QAction* saveAction = new QAction("Save", this);
    QAction* openAction = new QAction("Open", this);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(openAction);

    connect(saveAction, &QAction::triggered, this, &MyMainWindow::saveToFile);
    connect(openAction, &QAction::triggered, this, &MyMainWindow::loadFromFile);

    QMenu* editMenu = menuBar()->addMenu("Edit");
    QAction* appearanceAction = new QAction("Font & Color", this);
    editMenu->addAction(appearanceAction);

    connect(appearanceAction, &QAction::triggered,
            this, &MyMainWindow::changeAppearance);

    resize(300, 150);
}

void MyMainWindow::updateTime() {
    QString timeString = QTime::currentTime().toString("HH:mm:ss");
    timeLabel->setText(timeString);
    timeLabel->adjustSize();
}

void MyMainWindow::changeAppearance() {
    bool ok;
    QFont font = QFontDialog::getFont(&ok, currentFont, this);
    if (ok) {
        currentFont = font;
        timeLabel->setFont(currentFont);
    }

    QColor color = QColorDialog::getColor(currentColor, this);
    if (color.isValid()) {
        currentColor = color;
        timeLabel->setStyleSheet("color: " + color.name());
    }
}

void MyMainWindow::saveToFile() {
    QString fileName = QFileDialog::getSaveFileName(
        this, "Save", "", "Time Settings (*.fsb)");

    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Error", "Cannot open file");
        return;
    }

    QTextStream out(&file);
    out << "time_settings\n";
    out << currentFont.family() << "\n";
    out << currentFont.pointSize() << "\n";
    out << currentColor.red() << " "
        << currentColor.green() << " "
        << currentColor.blue() << "\n";
}

void MyMainWindow::loadFromFile() {
    QString fileName = QFileDialog::getOpenFileName(
        this, "Open", "", "Time Settings (*.fsb)");

    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Error", "Cannot open file");
        return;
    }

    QTextStream in(&file);
    QString header;
    in >> header;

    if (header != "time_settings") return;

    QString family;
    int size;
    int r, g, b;

    in >> family >> size >> r >> g >> b;

    currentFont = QFont(family, size);
    currentColor = QColor(r, g, b);

    timeLabel->setFont(currentFont);
    timeLabel->setStyleSheet("color: " + currentColor.name());
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyMainWindow window;
    window.show();
    return app.exec();
}
