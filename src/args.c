#include "args.h"

#define doc "modplay -- play module files easily from your terminal"
#define args_doc "FILE"

const char* argp_program_version = "modplay 0.0.1";
const char* argp_program_bug_address = "martyshkon@gmail.com";

static struct argp_option options[] = {
	{"loop",        'l', "COUNT",  OPTION_ARG_OPTIONAL, "Number of loops - loop infinitely if no value provided", 0},
	{"volume",      'v', "AMOUNT", 0,                   "Volume (0-100)",                                        0},
	{"sample-rate", 's', "RATE",   0,                   "Sample rate",                                           0},
	{"ui",          'u', 0,        0,                   "Use cool ncurses graphics",                             0},
	{0,             0,   0,        0,                   0,                                                       0}
};


static error_t parse_opt(int key, char* arg, struct argp_state* state)
{
	ParsedArgs* args = (ParsedArgs *) state->input;

	int parsedNum;

	switch (key)
	{
	case 'l':
		args->loops = arg ? atoi(arg) : -1;
		break;
	case 'v':
		parsedNum = atoi(arg);

		if (parsedNum < 0 || parsedNum > 100)
			argp_failure(state, 1, 0, "volume must be within 0-100");

		args->volume = (unsigned int) ((127.f / 100.f) * parsedNum + 1.f);

		break;
	case 's':
		args->sampleRate = atoi(arg);
		
		if (args->sampleRate <= 0)
			argp_failure(state, 1, 0, "sample rate must be more than zero (got %d)", args->sampleRate);

		break;
	case 'u':
		args->useUi = true;
		break;
	
	// Handling special cases
	case ARGP_KEY_ARG:
		if (state->arg_num >= 1)
		{
			argp_error(state, "too many arguments");
			argp_usage(state);
		}

		args->file = arg;

		break;
	case ARGP_KEY_END:
		if (state->arg_num < 1)
		{
			argp_error(state, "too little arguments");
			argp_usage(state);
		}

		break;
	
	default:
		return ARGP_ERR_UNKNOWN;
	}

	return 0;
}

static struct argp argp = {options, parse_opt, args_doc, doc, NULL, NULL, NULL};

ParsedArgs* parseArguments(int argc, char *argv[])
{
	ParsedArgs* args = (ParsedArgs *) malloc(sizeof(ParsedArgs)); // it's time for memory unsafety :japanese_ogre:
	
	args->loops = 0;
	args->volume = 128;
	args->sampleRate = 44100;

	argp_parse(&argp, argc, argv, 0, 0, args);

	return args;
}
