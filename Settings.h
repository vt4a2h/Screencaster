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
            return out << "-f pulse"
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
