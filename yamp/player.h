#pragma once

#include "playbackoptions.h"
#include "backend.h"

#include <portaudio.h>
#include <libopenmpt/libopenmpt.hpp>

namespace YAMP {
    class AudioBackend;

    class Player {
        PlaybackOptions& options;
        AudioBackend* backend;
        openmpt::module* module;

        friend YAMP::AudioBackend;
    public:
        Player(PlaybackOptions& options);
        ~Player();

        void play();

        bool hasFinished = false;
        bool getHasFinished();

        int readNextSamples(int bufferSize, float* buffer);

        std::string getMetadata(std::string key);
        double getDuration();

        int getNumOf(std::string key);
    };
};

