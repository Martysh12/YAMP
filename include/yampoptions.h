#pragma once

namespace YAMP
{
    struct YAMPOptions
    {
        int sampleRate;
        int channels;
        int volume;
        int repeat;

        static YAMP::YAMPOptions createDefault();
    };
};
