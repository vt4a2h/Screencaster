#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QSystemTrayIcon>

#include "Screencaster.h"

namespace
{
    const int minQuality = 0;
    const int maxQuality = 51;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mIcon(new QSystemTrayIcon(QIcon(":/icons/pic/play.png")))
    , mState(State::Default)
    , mScreencaster(new sc::Screencaster)
{
    ui->setupUi(this);

    configure();
}

MainWindow::~MainWindow()
{
}

MainWindow::State MainWindow::state() const
{
    return mState;
}

void MainWindow::start()
{
    mScreencaster->setSettings(readSettings());
    mScreencaster->start();

    auto errors = mScreencaster->errors();
    if (errors.isEmpty())
    {
        ui->btnStartStop->setText(tr("&Stop"));
        mIcon->setIcon(QIcon(":/icons/pic/stop.png"));
    }
}

void MainWindow::stop()
{
    mScreencaster->stop();
    ui->btnStartStop->setText(tr("&Start"));
    mIcon->setIcon(QIcon(":/icons/pic/start.png"));
}

sc::Settings MainWindow::readSettings()
{
    sc::VideoSettings vs { ui->leFPS->text().toUShort(), ui->leQuality->text().toUShort(),
                           ui->leWidth->text().toUInt(), ui->leHeight->text().toUInt(),
                           ui->leVideoCodec->text()    , ui->lePreset->text(),
                           ui->leProfile->text()       , ui->leViewport->text() };

    sc::AudioSettings as { ui->leACNumber->text().toUShort(), ui->leAudioCodec->text() };

    return sc::Settings { vs, as, ui->leOutput->text() };
}

void MainWindow::setState(MainWindow::State state)
{
    if (mState != state) {
        mState = state;
        emit stateChanged(mState);
    }
}

void MainWindow::configure()
{
    ui->leQuality->setValidator(new QIntValidator(minQuality, maxQuality, this));
    ui->btnStartStop->setFocus();

    mIcon->show();

    connect(ui->btnStartStop, &QPushButton::clicked, this,
            [this](){ setState(state() == State::Default ? State::Proccess : State::Default); });
    connect(this, &MainWindow::stateChanged, this, &MainWindow::onStateChanged);
}

void MainWindow::onStateChanged(MainWindow::State current)
{
    switch (current) {
        case State::Default:
            stop();
            break;

        case State::Proccess:
            start();
            break;

        default: ;
    }
}
