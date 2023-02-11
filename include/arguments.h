#pragma once

#include "yampoptions.h"

#include <argp.h>
#include <cstdlib>
#include <string>
#include <iostream>

extern const char* argp_program_version;
extern const char* argp_program_bug_address;

error_t parseOption(int key, char* arg, argp_state* state);

struct Arguments
{
    std::string file;
    int sampleRate;
    int channels;
    int volume;

    Arguments(int argc, char* argv[]);
    YAMP::YAMPOptions createYAMPOptions();
};
