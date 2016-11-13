#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QMenu>

#include "Screencaster.h"

namespace
{
    const int minQuality = 0;
    const int maxQuality = 51;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mTrayIcon(new QSystemTrayIcon(QIcon(":/icons/pic/start.png")))
    , mState(ProcessState::Default)
    , mScreencaster(new sc::Screencaster)
{
    ui->setupUi(this);

    configure();
}

MainWindow::~MainWindow()
{
}

MainWindow::ProcessState MainWindow::state() const
{
    return mState;
}

void MainWindow::toggleState()
{
    setState(state() == ProcessState::Default ? ProcessState::Proccess : ProcessState::Default);
}

void MainWindow::start()
{
    // Remove previous output if needed
    if (ui->cbOverwriteOutputFile->isChecked()) {
        QFile output(ui->leOutput->text());
        if (output.exists())
            output.remove();
    }

    // Start recording
    mScreencaster->setSettings(readSettings());
    mScreencaster->start();

    // Check errors
    auto errors = mScreencaster->errors();
    if (errors.isEmpty()) {
        ui->btnStartStop->setText(tr("&Stop"));
        mTrayIcon->setIcon(QIcon(":/icons/pic/stop.png"));
        enableSettingsWidgets(false);
    }
}

void MainWindow::stop()
{
    mScreencaster->stop();
    ui->btnStartStop->setText(tr("&Start"));
    mTrayIcon->setIcon(QIcon(":/icons/pic/start.png"));
    enableSettingsWidgets(true);
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

void MainWindow::enableSettingsWidgets(bool enable)
{
    ui->gbVideoSettings->setEnabled(enable);
    ui->gbGeometry->setEnabled(enable);
    ui->gbAudioSettings->setEnabled(enable);
    ui->gbOutput->setEnabled(enable);
}

void MainWindow::setState(MainWindow::ProcessState state)
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

    mTrayIcon->show();
    auto menu = new QMenu(this);
    menu->addAction(tr("Hide"), [this, menu = menu] {
        if (isVisible()) {
            hide();
            menu->actions()[0]->setText(tr("Show"));
        } else {
            show();
            menu->actions()[0]->setText(tr("Hide"));
        }
    });
    mTrayIcon->setContextMenu(menu);


    connect(ui->btnStartStop,   &QPushButton::clicked,       this, &MainWindow::toggleState);
    connect(this,               &MainWindow::stateChanged,   this, &MainWindow::onProcessStateChanged);
    connect(ui->tbChooseOutput, &QToolButton::clicked,       this, &MainWindow::onChooseOutputClicked);
    connect(mTrayIcon.get(),    &QSystemTrayIcon::activated, this, &MainWindow::onTrayIconActivated);
}

void MainWindow::onProcessStateChanged(MainWindow::ProcessState current)
{
    switch (current) {
        case ProcessState::Default:
            stop();
            break;

        case ProcessState::Proccess:
            start();
            break;

        default: ;
    }
}

void MainWindow::onChooseOutputClicked()
{
    auto file = QFileDialog::getSaveFileName(this, tr("Specify output file"), QDir::homePath());
    if (!file.isEmpty())
        ui->leOutput->setText(file);
}

void MainWindow::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
        toggleState();
}
