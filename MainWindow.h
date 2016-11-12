#pragma once

#include <memory>

#include <QMainWindow>

#include "Settings.h"

namespace Ui {
    class MainWindow;
}

namespace sc {
    class Screencaster;
}

class QSystemTrayIcon;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(State mState READ state WRITE setState NOTIFY stateChanged)
    Q_ENUMS(State)

public: // Types
    enum class State {Default, Proccess};

public: // Methods
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void stateChanged(State mState);

private slots:
    void onStateChanged(State current);

private:
    std::unique_ptr<Ui::MainWindow> ui;

    std::unique_ptr<QSystemTrayIcon> mIcon;

    State mState;
    std::unique_ptr<sc::Screencaster> mScreencaster;

    void configure();

    void setState(State mState);
    State state() const;

    void start();
    void stop();

    sc::Settings readSettings();
};
