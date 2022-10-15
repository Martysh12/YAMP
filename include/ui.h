#ifndef UI_H
#define UI_H

#define _GNU_SOURCE

#include "args.h"

#include <ncurses.h>
#include <libopenmpt/libopenmpt.h>

#include <string.h>
#include <unistd.h>

void getNoteStringFromValue(char* s, int note);
void getInstStringFromValue(char* s, int inst);

void getTimeStringFromSeconds(char* s, double seconds);

double clamp(double val, double min, double max);

void initUI(void);

int drawUI(ParsedArgs* args, openmpt_module* file, int frame, int file_size);

void stopUI(void);

#endif
