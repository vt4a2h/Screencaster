#include "Screencaster.h"

namespace sc {

    Screencaster::Screencaster(QObject *parent)
        : QObject(parent)
    {
        mProcess.setProgram("ffmpeg");
    }

    void Screencaster::start()
    {
        if (mProcess.state() != QProcess::Running)
        {
            mProcess.start(QProcess::NotOpen);
            mProcess.waitForStarted();
        }
    }

    void Screencaster::stop()
    {
        if (mProcess.state() == QProcess::Running)
        {
            mProcess.terminate();
            mProcess.waitForFinished();
        }
    }

    Settings Screencaster::settings() const
    {
        return mSettings;
    }

    void Screencaster::setSettings(Settings const& settings)
    {
        mSettings = settings;

        QString args;
        QTextStream s(&args);
        s << mSettings;
        mProcess.setArguments(args.split(" "));
    }

    QString Screencaster::errors() const
    {
        return mProcess.state() != QProcess::Running ? mProcess.errorString() : "";
    }

} // namespace sc
