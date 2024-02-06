#ifndef DELAY_H
#define DELAY_H

#include "../../Parameters/AudioParameter.h"

/************************************************************//**
 *  Class name: Delay
 *  Function: Processes delay effect for block of input sanples
 ***************************************************************/
using namespace daisysp;

//extern DelayLine<float, MAXDELAY> DSY_SDRAM_BSS delayLine;

class Delay
{
public:

    void init(DaisySeed* seed, DelayLine<float, MAXDELAY>* dl[2]);
    void tick();

    void setBypass(int b) { bypass = b; }
    void setDelay(size_t s) { delayLine[L]->SetDelay(s), delayLine[R]->SetDelay(s); }
    //void setDelayR(size_t s) {delayLine[r]} add for stereo delay
    void setBounce(float b) { bounce = b; }
    void setAmount(float a) { amount = a; }

    void prepare();
    void processBlock(float* input[2], size_t size, size_t rp); 

private:

    AudioParameter<int> bypassParam;
    AudioParameter<size_t> sizeParam;
    AudioParameter<float> bounceParam;
    AudioParameter<float> amountParam;

    int bypass;
    size_t size;
    float bounce;
    float amount;

    DelayLine<float, MAXDELAY>* delayLine[2];
};

#endif