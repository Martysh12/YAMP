#include "yampoptions.h"

YAMP::YAMPOptions YAMP::YAMPOptions::createDefault() {
    YAMP::YAMPOptions options;

    options.sampleRate = 44100;
    options.channels = 2;
    options.volume = 0;
    options.repeat = 0;

    return options;
}