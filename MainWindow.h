#pragma once

#include <memory>

#include <QMainWindow>
#include <QSystemTrayIcon>

#include "Settings.h"

namespace Ui {
    class MainWindow;
}

namespace sc {
    class Screencaster;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(ProcessState mState READ state WRITE setState NOTIFY stateChanged)
    Q_ENUMS(ProcessState)

public: // Types
    enum class ProcessState {Default, Proccess};

public: // Methods
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void stateChanged(ProcessState mState);

private slots:
    void onProcessStateChanged(ProcessState current);
    void onChooseOutputClicked();
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void toggleState();

private:
    std::unique_ptr<Ui::MainWindow> ui;

    std::unique_ptr<QSystemTrayIcon> mTrayIcon;

    ProcessState mState;
    std::unique_ptr<sc::Screencaster> mScreencaster;

    void configure();

    void setState(ProcessState mState);
    ProcessState state() const;

    void start();
    void stop();

    sc::Settings readSettings();

    void enableSettingsWidgets(bool enable = true);
};
