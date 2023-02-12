#include "arguments.h"

const char* argp_program_version = "yamp 0.1.0";
const char* argp_program_bug_address = "<martyshkon@gmail.com>";

error_t parseOption(int key, char* arg, argp_state* state)
{
    Arguments* args = reinterpret_cast<Arguments *>(state->input);

    char* endptr = NULL; // Needed for strtol() error check

    switch (key)
    {
    case 'r':
        args->sampleRate = strtol(arg, &endptr, 10);
        
        // Skip the strtol() check, sample rate <1000 will cause a seg-fault.
        if (args->sampleRate < 1000)
        {
            argp_error(state, "invalid sample rate");
        }

        break;

    case 'v':
        args->volume = strtol(arg, &endptr, 10);
        
        if (errno != 0 && args->volume == 0 && arg == endptr)
        {
            argp_error(state, "invalid volume");
        }

        break;

    case 'm':
        args->channels = 1;
        break;

    case 's':
        args->channels = 2;
        break;

    case 'q':
        args->channels = 4;
        break;

    case ARGP_KEY_ARG:
        if (state->arg_num >= 1)
        {
            argp_error(state, "too many arguments");
        }
        else
        {
            args->file = arg;
        }

        break;

    case ARGP_KEY_END:
        if (state->arg_num < 1)
        {
            argp_error(state, "too little arguments");
        }

        break;

    default:
        return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

Arguments::Arguments(int argc, char* argv[]) :
    sampleRate(-1),
    channels(-1),
    volume(INT_MIN)
{
    std::string doc = "tracker music player";
    std::string argsDoc = "FILE";

    argp_option options[] = {
        {"sample-rate", 'r', "RATE",   0, "Sample rate"},
        {"volume",      'v', "AMOUNT", 0, "Volume in decibel. Default: 0."},
        {"mono",        'm', 0,      0, "1 channel"},
        {"stereo",      's', 0,      0, "2 channels"},
        {"quad",        'q', 0,      0, "4 channels"},
        {0,             0,   0,      0, 0}
    };

    argp parser = {options, parseOption, argsDoc.c_str(), doc.c_str()};

    argp_parse(&parser, argc, argv, 0, 0, this);
}

YAMP::YAMPOptions Arguments::createYAMPOptions()
{
    YAMP::YAMPOptions options = YAMP::YAMPOptions::createDefault();
    if (sampleRate != -1) options.sampleRate = sampleRate;
    if (channels != -1)   options.channels = channels;
    if (volume != INT_MIN)   options.volume = volume;

    return options;
}
