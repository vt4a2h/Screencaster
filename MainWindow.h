#pragma once

#include <memory>

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_ENUMS(State)

public: // Types
    enum class State {Default, Proccess};

public: // Methods
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onStateChanged(State previous, State current);

private:
    std::unique_ptr<Ui::MainWindow> ui;
    State mState;

    void configure();
};

