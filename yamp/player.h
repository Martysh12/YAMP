#pragma once

#include "playbackoptions.h"
#include "backend.h"

#include <portaudio.h>
#include <libopenmpt/libopenmpt.hpp>

namespace YAMP {
    class Player {
        PlaybackOptions& options;
        openmpt::module* module;

        bool hasFinished = false;

    public:
        Player(PlaybackOptions& options);
        ~Player();

        void play();
        int readNextSamples(int bufferSize, float* buffer);

        bool getHasFinished();

        std::string getMetadata(std::string key);
        double getDuration();

        int getNumOf(std::string key);
    };
};

