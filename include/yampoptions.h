#pragma once

namespace YAMP
{
    struct YAMPOptions
    {
        int sampleRate;
        int channels;
        int volume;

        static YAMP::YAMPOptions createDefault();
    };
};
