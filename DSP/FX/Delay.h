#ifndef DELAY_H
#define DELAY_H

#include "../../Parameters/AudioParameter.h"
#include "../../Parameters/BinaryParameter.h"

/************************************************************//**
 *  Class name: Delay
 *  Function: Processes delay effect for block of input samples
 ***************************************************************/
using namespace daisysp;

class Delay
{
public:

    void init(DaisySeed* seed, DelayLine<float, MAXDELAY>* dl[2]);
    void tick();

    inline void setBypass() { bypass.value = !bypass.value; }
    inline void setDelay(size_t s) { delayLine[L]->SetDelay(s), delayLine[R]->SetDelay(s); }
    inline void setBounce(float b) { bounce.value = b; }
    inline void setAmount(float a) { amount.value = a; }

    void processBlock(float* buffer[2], size_t size); 

private:

    BinaryParameterWrapper bypass;
    AudioParameter<size_t> size;
    AudioParameterWrapper<float> bounce;
    AudioParameterWrapper<float> amount;

    DelayLine<float, MAXDELAY>* delayLine[2];
};

#endif