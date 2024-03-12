#ifndef DELAY_H
#define DELAY_H

#include "../../Parameters/AudioParameter.h"
#include "../../Parameters/BinaryParameter.h"
#include "../../Parameters/DefaultValues.h"

/************************************************************//**
 *  Class name: Delay
 *  Function: Processes delay effect for block of input samples
 ***************************************************************/
using namespace daisysp;

class Delay
{
public:

    void init(DaisySeed* seed, DelayLine<float, MAXDELAY>* dl[2]);
    void setDefaultValues();
    void tick();

    inline void setBypass() { bypass.value = !bypass.value; }
    inline void setDelay(size_t s) { delayLine[L]->SetDelay(s), delayLine[R]->SetDelay(s); }
    inline void setFeedback(float b) { feedback.value = b; }
    inline void setAmount(float a) { amount.value = a; }

    void processBlock(float* input[2], size_t size); 

private:

    BinaryParameterWrapper bypass;
    AudioParameterWrapper<float> amount;
    AudioParameter<size_t> size;
    AudioParameterWrapper<float> feedback;

    DelayLine<float, MAXDELAY>* delayLine[2];
};

#endif