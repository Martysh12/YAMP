#pragma once

namespace YAMP
{
    struct YAMPOptions
    {
        int sampleRate;
        int channels;

        static YAMP::YAMPOptions createDefault();
    };
};
