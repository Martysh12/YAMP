#pragma once

#include <string>

namespace YAMP
{
    struct PlaybackOptions
    {
        std::string file;
        unsigned int sampleRate = 44100;
        unsigned int channels = 2;
        int volume = 0;
        int repeat = 0;

        static PlaybackOptions fromArguments(int argc, char** argv);
    };
};
