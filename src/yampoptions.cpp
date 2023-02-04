#include "yampoptions.h"

YAMP::YAMPOptions YAMP::YAMPOptions::createDefault() {
    YAMP::YAMPOptions options;

    options.sampleRate = 44100;
    options.channels = 2;

    return options;
}