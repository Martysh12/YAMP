#ifndef ARGS_H
#define ARGS_H

#include <argp.h>

#include <stdbool.h>
#include <stdlib.h>

extern const char* argp_program_version;
extern const char* argp_program_bug_address;

typedef struct _parsedArgs {
	char* file;
	int loops;
	unsigned int volume;
	unsigned int sampleRate;
	bool useUi;
} ParsedArgs;


ParsedArgs* parseArguments(int argc, char *argv[]);

#endif
