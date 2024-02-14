#ifndef DELAY_H
#define DELAY_H

#include "../../Parameters/AudioParameter.h"

/************************************************************//**
 *  Class name: Delay
 *  Function: Processes delay effect for block of input sanples
 ***************************************************************/
using namespace daisysp;

class Delay
{
public:

    void init(DaisySeed* seed, DelayLine<float, MAXDELAY>* dl[2]);
    void tick();

    inline void setBypass(int b) { bypass.value = b; }
    inline void setDelay(size_t s) { delayLine[L]->SetDelay(s), delayLine[R]->SetDelay(s); }
    inline void setBounce(float b) { bounce.value = b; }
    inline void setAmount(float a) { amount.value = a; }

    void prepare();
    void processBlock(float* input[2], size_t size, size_t readPos); 

private:

    ParameterWrapper<int> bypass;
    AudioParameter<size_t> size;
    ParameterWrapper<float> bounce;
    ParameterWrapper<float> amount;

    DelayLine<float, MAXDELAY>* delayLine[2];
};

#endif