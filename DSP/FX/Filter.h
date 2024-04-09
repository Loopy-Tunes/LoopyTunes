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

    void scaleFreq(float f);

    void setBypass(float b) { bypass.value = b; }
    void setFreq(float f) { filter.SetFreq(f); }
    void setReso(float r) { filter.SetRes(r); }
    void setMode(float m);

    void processBlock(float* buffer[2], size_t size);

private:

    enum Mode
    {
        LOWPASS = 0,
        HIGHPASS
    } filterMode;

    Svf filter;

    float lpMin, lpMax;
    float hpMin, hpMax;

    SteppedParameterWrapper bypass;
    SteppedParameter mode;
    SteppedParameter freq;
    SteppedParameter reso;
};

#endif