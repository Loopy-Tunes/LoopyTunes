#ifndef DELAY_H
#define DELAY_H

#include "../../Parameters/AudioParameter.h"

/************************************************************//**
 *  Class name: Delay
 *  Function: Processes delay effect for block of input sanples
 ***************************************************************/
using namespace daisysp;

DelayLine<float, MAXDELAY> DSY_SDRAM_BSS delayLine;

class Delay
{
public:

    void init();
    void tick();

    void prepare();
    void process();

private:

    AudioParameter<float> size;
    AudioParameter<float> bounce;
    AudioParameter<float> amount;
};

#endif