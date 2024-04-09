#ifndef DELAY_H
#define DELAY_H

#include "../../Parameters/DefaultValues.h"
#include "../../Drivers/EncoderDriver.h"

#define MAXDELAY 240000 // 5 second max delay

/************************************************************//**
 *  Class name: Delay
 *  Function: Processes delay effect for block of input samples
 ***************************************************************/
using namespace daisysp;

class Delay
{
public:

    void init(EncoderDriver* driver, int trackID, DelayLine<float, MAXDELAY>* dl[2]);
    void setDefaultValues();

    inline void setBypass(bool b) { isBypass = b; }
    inline void setDelay(size_t s) { delayLine[0]->SetDelay(s), delayLine[1]->SetDelay(s); }
    inline void setFeedback(float b) { feedback.value = b; }
    inline void setAmount(float a) { amount.value = a; }

    void processBlock(float* input[2], size_t size); 

private:

    template<typename type>
    type toSize(type toConvert)
    {
        return round((size_t)toConvert);
    }

    bool isBypass;
    SteppedParameterWrapper amount;
    SteppedParameterWrapper size;
    SteppedParameterWrapper feedback;

    DelayLine<float, MAXDELAY>* delayLine[2];
};

#endif