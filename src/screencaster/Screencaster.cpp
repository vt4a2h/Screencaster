/*****************************************************************************
**
** The MIT License
**
** Copyright (c) 2016-2020 Vitaly Fanaskov (vt4a2h@gmail.com)
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
