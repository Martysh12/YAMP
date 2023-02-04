#include "yampportaudio.h"

#include "yampplayer.h"

int YAMP::paCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData)
{
    YAMPPlayer* yamp = reinterpret_cast<YAMPPlayer *>(userData);

    yamp->readNextSamples(framesPerBuffer, reinterpret_cast<float *>(outputBuffer));

    return paContinue;
}