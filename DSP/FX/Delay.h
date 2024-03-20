#ifndef DELAY_H
#define DELAY_H

#include "../../Parameters/AudioParameter.h"
#include "../../Parameters/BinaryParameter.h"
#include "../../Parameters/DefaultValues.h"
#include "../../Drivers/EncoderDriver.h"
#include "../../Utils/Helpers.h"

/************************************************************//**
 *  Class name: Delay
 *  Function: Processes delay effect for block of input samples
 ***************************************************************/
using namespace daisysp;

class Delay
{
public:

    void init(EncoderDriver* driver, std::string trackID, DelayLine<float, MAXDELAY>* dl[2]);
    void setDefaultValues();
    void tick();

    inline void setBypass(float b) { bypass.value = b; }
    inline void setDelay(size_t s) { delayLine[L]->SetDelay(s), delayLine[R]->SetDelay(s); }
    inline void setFeedback(float b) { feedback.value = b; }
    inline void setAmount(float a) { amount.value = a; }

    void processBlock(float* input[2], size_t size); 

private:

    SteppedParameterWrapper bypass;
    SteppedParameterWrapper amount;
    SteppedParameterWrapper size;
    SteppedParameterWrapper feedback;

    DelayLine<float, MAXDELAY>* delayLine[2];
};

#endif