/*
 * modes - configurable list of game modes and their properties
 */
#include "modes.h"

mode *current_mode;
unsigned int mode_index;
unsigned int mode_index_prev;
double current_ratio = 4.0 / 3.0;
