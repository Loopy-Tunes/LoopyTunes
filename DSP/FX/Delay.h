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

    void setBypass(int b) { bypass = b; }
    void setSize(float s) { buffer.SetDelay(s); }
    void setBounce(float b) { bounce = b; }
    void setAmount(float a) { amount = a; }

    void prepare();
    void processBlock(float* input[2], size_t size, size_t rp); 

private:

    AudioParameter<int> bypassParam;
    AudioParameter<float> sizeParam;
    AudioParameter<float> bounceParam;
    AudioParameter<float> amountParam;

    int bypass;
    float size;
    float bounce;
    float amount;
};

#endif