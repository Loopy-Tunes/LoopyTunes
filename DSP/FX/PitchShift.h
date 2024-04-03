#ifndef PITCHSHIFTER_H
#define PITCHSHIFTER_H

#include "../../Parameters/AudioParameter.h"
#include "../../Parameters/DefaultValues.h"
#include "../../Drivers/EncoderDriver.h"

/***************************************************************************************//**
 *  Class name: PitchShift
 *  Function: Wrapper for DaisySP pitch shifter class that pitch shifts a block of samples
 ******************************************************************************************/
using namespace daisysp;

class PitchShift
{
public:

    void init(EncoderDriver* driver, int trackID);
    void setDefaultValues();
    void tick();

    void setBypass(float b) { bypass.value = b; }
    void setAmount(float a) { amount.value = a; }

    void process(float* input[2], size_t size);

private:

    float buffer[2][BLOCKLENGTH];
    daisysp::PitchShifter shifter;

    SteppedParameterWrapper bypass;
    SteppedParameterWrapper amount;
    SteppedParameterWrapper semitones;
};

#endif