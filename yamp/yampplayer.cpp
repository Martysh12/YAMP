#include "yampplayer.h"

#include <fstream>
#include <iomanip>

void YAMP::YAMPPlayer::checkPaError(PaError err)
{
    if (err != paNoError)
    {
        throw std::runtime_error(Pa_GetErrorText(err));
    }
}

YAMP::YAMPPlayer::YAMPPlayer(PlaybackOptions& options) :
    m_options(options),
    m_hasFinished(false)
{

    std::ifstream f(options.file);

    if (!f.is_open())
    {
        std::cout << "Couldn't open file " << std::quoted(options.file) << "." << std::endl;
        throw std::runtime_error("some error this will be revamped later");
    }

    m_module = new openmpt::module(f);

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
    delete m_module;
    checkPaError(Pa_Terminate());
}

void YAMP::YAMPPlayer::play()
{
    m_module->set_render_param(openmpt::module::RENDER_MASTERGAIN_MILLIBEL, m_options.volume * 100);
    m_module->set_repeat_count(m_options.repeat);

    checkPaError(Pa_StartStream(m_stream));
}

int YAMP::YAMPPlayer::readNextSamples(int bufferSize, float* buffer)
{
    switch (m_options.channels)
    {
    case 1:
        return m_module->read(
            m_options.sampleRate,
            bufferSize,
            buffer
        );
    case 2:
        return m_module->read_interleaved_stereo(
            m_options.sampleRate,
            bufferSize,
            buffer
        );
    case 4:
        return m_module->read_interleaved_quad(
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

bool YAMP::YAMPPlayer::hasFinished()
{
    return m_hasFinished;
}

void YAMP::YAMPPlayer::setHasFinished(bool hasFinished)
{
    m_hasFinished = hasFinished;
}

std::string YAMP::YAMPPlayer::getMetadata(std::string key)
{
    return m_module->get_metadata(key);
}

double YAMP::YAMPPlayer::getDuration()
{
    return m_module->get_duration_seconds();
}

int YAMP::YAMPPlayer::getNumOf(std::string key)
{
    if (key == "channels") return m_module->get_num_channels();
    if (key == "instruments") return m_module->get_num_instruments();
    if (key == "orders") return m_module->get_num_orders();
    if (key == "patterns") return m_module->get_num_patterns();
    if (key == "samples") return m_module->get_num_samples();
    if (key == "subsongs") return m_module->get_num_subsongs();

    return 0;
}