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
#pragma once

#include <QString>
#include <QTextStream>

namespace sc {

    /// Available video settings
    struct VideoSettings
    {
        ushort fps;
        ushort quality;
        uint   width;
        uint   height;
        QString videoCodec;
        QString encodingPreset;
        QString profile;
        QString viewPort;

        friend QTextStream &operator <<(QTextStream &out, VideoSettings const & s)
        {
            return out << "-f x11grab"
                       << " -video_size " << s.width << "x" << s.height
                       << " -framerate "  << s.fps
                       << " -i "          << s.viewPort
                       << " -vcodec "     << s.videoCodec
                       << " -preset "     << s.encodingPreset
                       << " -profile:v "  << s.profile
                       << " -crf "        << s.quality
                       << " -pix_fmt "    << "yuv420p"
                       << " -r "          << s.fps;
        }
    };

    /// Available audio settings
    struct AudioSettings
    {
        ushort channelsCount;
        QString audioCodec;

        friend QTextStream &operator <<(QTextStream &out, AudioSettings const & s)
        {
            return out << "-f "       << "pulse"
                       << " -i "      << "default"
                       << " -ac "     << s.channelsCount
                       << " -acodec " << s.audioCodec;
        }
    };

    /// Available settings
    struct Settings
    {
        VideoSettings videoSettings;
        AudioSettings audioSettings;

        QString output;

        friend QTextStream &operator <<(QTextStream &out, Settings const & s)
        {
            return out << s.audioSettings << " " << s.videoSettings << " " << s.output;
        }
    };

} // namespace sc
