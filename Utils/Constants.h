#include "stddef.h"

#define BLOCKLENGTH 4
#define SAMPLERATE 48000
#define DURATION 10

#define MAXDELAY 240000 // 5 second max delay

#define L 0
#define R 1

#define ADCINPUTS 4
#define SUBBLOCKSIZE 1024

#define NO_OPT __attribute__((optimize(0)))