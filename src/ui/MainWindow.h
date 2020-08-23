/*****************************************************************************
**
** The MIT License
**
** Copyright (c) 2016 Vitaly Fanaskov (vt4a2h@gmail.com)
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
** THE SOFTWARE.
**
*****************************************************************************/
#pragma once

#include <memory>

#include <QtWidgets/QMainWindow>
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
