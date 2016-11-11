#include "MainWindow.h"
#include "ui_MainWindow.h"

namespace
{
    const int minQuality = 0;
    const int maxQuality = 51;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mState(State::Default)
{
    ui->setupUi(this);

    configure();
}

MainWindow::~MainWindow()
{
}

void MainWindow::onStateChanged(MainWindow::State, MainWindow::State current)
{
}

void MainWindow::configure()
{
    ui->leQuality->setValidator(new QIntValidator(minQuality, maxQuality, this));
    ui->btnStartStop->setFocus();
}
