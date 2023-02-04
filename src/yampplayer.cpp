#include "yampplayer.h"

void YAMP::YAMPPlayer::checkPaError(PaError err)
{
    if (err != paNoError)
    {
        throw std::runtime_error(Pa_GetErrorText(err));
    }
}

YAMP::YAMPPlayer::YAMPPlayer(std::istream& file, YAMPOptions& options) :
    m_module(file),
    m_options(options)
{
    checkPaError(Pa_Initialize());

    checkPaError(
        Pa_OpenDefaultStream(
            &m_stream,
            0,
            m_options.channels,
            paFloat32,
            m_options.sampleRate,
            paFramesPerBufferUnspecified,
            YAMP::paCallback,
            this
        )
    );
}

YAMP::YAMPPlayer::~YAMPPlayer()
{
    checkPaError(Pa_Terminate());
}

void YAMP::YAMPPlayer::play()
{
    checkPaError(Pa_StartStream(m_stream));
}

int YAMP::YAMPPlayer::readNextSamples(int bufferSize, float* buffer)
{
    switch (m_options.channels)
    {
    case 1:
        return m_module.read(
            m_options.sampleRate,
            bufferSize,
            buffer
        );
    case 2:
        return m_module.read_interleaved_stereo(
            m_options.sampleRate,
            bufferSize,
            buffer
        );
    case 4:
        return m_module.read_interleaved_quad(
            m_options.sampleRate,
            bufferSize,
            buffer
        );
    default:
        for (int i = 0; i < bufferSize; ++i)
        {
            buffer[i] = 0.0f;
        }
        return bufferSize;
    }
}
