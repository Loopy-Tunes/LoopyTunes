#ifndef FILTER_H
#define FILTER_H

#include "../../Parameters/DefaultValues.h"
#include "../../Drivers/EncoderDriver.h"
#include "../../Utils/Constants.h"

/**********************************************************************************************//**
 *  Class name: Filter
 *  Function: Wrapper for DaisySP ladder filter class that applies a filter to a block of samples
 *************************************************************************************************/
using namespace daisysp;

class Filter
{
public:

    void init(EncoderDriver* driver, int trackID);
    void setDefaultValues();
    
    void setBypass() { isBypass = !isBypass; }
    void setFreq(float f) { filter.SetFrequency(f); }
    void setMode(float m);

    void processBlock(float* buffer[2], size_t size);

private:

    OnePole filter;

    bool isBypass;
    SteppedParameter mode;
    SteppedParameter freq;
};

#endif