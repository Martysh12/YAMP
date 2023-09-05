#include "playbackoptions.h"

#include <argp.h>
#include <stdexcept>

const char* argp_program_version = "yamp 0.1.0";
const char* argp_program_bug_address = "https://github.com/Martysh12/YAMP/issues";

const char* doc = "tracker music player";
const char* argsDoc = "FILE";

static error_t parseOption(int key, char* arg, argp_state* state) {
    YAMP::PlaybackOptions* args = reinterpret_cast<YAMP::PlaybackOptions *>(state->input);

    char const* error_msg;

    switch (key) {
    case 'r':
        error_msg = "invalid sample rate";

        try {
            args->sampleRate = std::stoi(arg);
        } catch (std::invalid_argument& err) {
            goto error;
        }
        
        if (args->sampleRate < 1000) {
            goto error;
        }

        break;

    case 'v':
        error_msg = "invalid volume";

        try {
            args->volume = std::stoi(arg);
        } catch (std::invalid_argument& err) {
            goto error;
        }

        break;

    case 'l':
        error_msg = "invalid repeat";

        if (arg == NULL) {
            args->repeat = -1;
            break;
        }

        try {
            args->repeat = std::stoi(arg);
        } catch (std::invalid_argument& err) {
            goto error;
        }

        if (args->repeat < -1) {
            goto error;
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
        if (state->arg_num >= 1) {
            argp_error(state, "too many arguments");
        } else {
            args->file = arg;
        }

        break;

    case ARGP_KEY_END:
        if (state->arg_num < 1) {
            argp_error(state, "too little arguments");
        }

        break;

    default:
        return ARGP_ERR_UNKNOWN;
    }

    return 0;

error:
    argp_error(state, error_msg);
    return 1;
}

YAMP::PlaybackOptions YAMP::PlaybackOptions::fromArguments(int argc, char** argv) {
    PlaybackOptions playbackOptions;

    argp_option options[] = {
        {"sample-rate", 'r', "RATE",   0,                   "sample rate",       0},
        {"volume",      'v', "AMOUNT", 0,                   "volume in decibel", 0},
        {"loop",        'l', "AMOUNT", OPTION_ARG_OPTIONAL, "amount of repeats", 0},
        {"mono",        'm', 0,        0,                   "1 channel",         0},
        {"stereo",      's', 0,        0,                   "2 channels",        0},
        {"quad",        'q', 0,        0,                   "4 channels",        0},
        {0,             0,   0,        0,                   0,                   0}
    };

    argp parser = {options, parseOption, argsDoc, doc, NULL, NULL, NULL};

    argp_parse(&parser, argc, argv, 0, 0, &playbackOptions);

    return playbackOptions;
}
