#ifndef PITCHSHIFTER_H
#define PITCHSHIFTER_H

#include "../../Parameters/AudioParameter.h"
#include "../../Parameters/BinaryParameter.h"
#include "../../Parameters/DefaultValues.h"
#include "../../Drivers/EncoderDriver.h"

/************************************************************//**
 *  Class name: PitchShift
 *  Function: Pitch shifts a block of input samples n semitones
 ***************************************************************/
using namespace daisysp;

class PitchShift
{
public:

    void init(DaisySeed* seed);
    void setDefaultValues();
    void tick();

    void process(float* input[2], size_t size);

    void setBypass() { bypass.value = !bypass.value; }

private:

    float buffer[2][BLOCKLENGTH];
    daisysp::PitchShifter shifter;

    BinaryParameterWrapper bypass;
    AudioParameterWrapper<float> amount;
    AudioParameter<int> semitones;
    AudioParameter<float> rand;
};

#endif