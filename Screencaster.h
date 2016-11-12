#pragma once

#include <QObject>
#include <QProcess>

#include "Settings.h"

namespace sc {

    /// Class for making screencasts. Starts ffmpeg as a separate process with specified settings
    class Screencaster : public QObject
    {
        Q_OBJECT

    public:
        Screencaster(QObject * parent = nullptr);

        Settings settings() const;
        void setSettings(Settings const& settings);

        QString errors() const;

    public slots:
        void start();
        void stop();

    private:
        Settings mSettings;
        QProcess mProcess;
    };

} // namespace sc
