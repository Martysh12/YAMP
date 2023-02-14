#pragma once

#include "yampoptions.h"
#include "yampportaudio.h"

#include <portaudio.h>
#include <libopenmpt/libopenmpt.hpp>

namespace YAMP
{
    class YAMPPlayer
    {
        YAMPOptions& m_options;
        openmpt::module m_module;
        PaStream* m_stream;

        bool m_hasFinished;

        void checkPaError(PaError err);

    public:
        YAMPPlayer(std::istream& file, YAMPOptions& options);
        ~YAMPPlayer();

        void play();
        int readNextSamples(int bufferSize, float* buffer);

        bool hasFinished();
        void setHasFinished(bool hasFinished);

        std::string getMetadata(std::string& key);
    };
};

