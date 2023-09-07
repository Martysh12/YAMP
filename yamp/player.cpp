#include "player.h"

#include <fstream>

YAMP::Player::Player(PlaybackOptions& options) :
    options(options)
{

    std::ifstream f(options.file);

    if (!f.is_open()) {
        throw std::runtime_error(std::string{"Couldn't open file \""} + options.file + '"');
    }

    this->module = new openmpt::module(f);

    this->backend = new YAMP::AudioBackend(this);
}

YAMP::Player::~Player() {
    delete this->module;
    delete this->backend;
}

void YAMP::Player::play() {
    this->module->set_render_param(openmpt::module::RENDER_MASTERGAIN_MILLIBEL, this->options.volume * 100);
    this->module->set_repeat_count(this->options.repeat);
    this->backend->start();
}

int YAMP::Player::readNextSamples(int bufferSize, float* buffer) {
    switch (this->options.channels) {
    case 1:
        return this->module->read(
            this->options.sampleRate,
            bufferSize,
            buffer
        );
    case 2:
        return this->module->read_interleaved_stereo(
            this->options.sampleRate,
            bufferSize,
            buffer
        );
    case 4:
        return this->module->read_interleaved_quad(
            this->options.sampleRate,
            bufferSize,
            buffer
        );
    }

    return 0;
}

bool YAMP::Player::getHasFinished() {
    return this->hasFinished;
}

std::string YAMP::Player::getMetadata(std::string key) {
    return this->module->get_metadata(key);
}

double YAMP::Player::getDuration() {
    return this->module->get_duration_seconds();
}

int YAMP::Player::getNumOf(std::string key) {
    if (key == "channels") return this->module->get_num_channels();
    if (key == "instruments") return this->module->get_num_instruments();
    if (key == "orders") return this->module->get_num_orders();
    if (key == "patterns") return this->module->get_num_patterns();
    if (key == "samples") return this->module->get_num_samples();
    if (key == "subsongs") return this->module->get_num_subsongs();

    return 0;
}
