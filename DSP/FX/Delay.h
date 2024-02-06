#ifndef DELAY_H
#define DELAY_H

#include "../../Parameters/AudioParameter.h"

/************************************************************//**
 *  Class name: Delay
 *  Function: Processes delay effect for block of input sanples
 ***************************************************************/
using namespace daisysp;

extern DelayLine<float, MAXDELAY> DSY_SDRAM_BSS buffer;

class Delay
{
public:

    void init(DaisySeed* seed);
    void tick();

    void prepare();
    void processBlock(float* input[2], size_t size, size_t rp); 

private:

    AudioParameter<int> bypass;
    AudioParameter<float> size;
    AudioParameter<float> bounce;
    AudioParameter<float> amount;
};

#endif