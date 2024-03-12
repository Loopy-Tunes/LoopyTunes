#ifndef REVERB_H
#define REVERB_H

#include "../../../Parameters/AudioParameter.h"
#include "../../../Parameters/BinaryParameter.h"
#include "../../../Parameters/DefaultValues.h"
#include "revmodel.hpp"

/*********************************************************************//**
 *  Class name: Reverb
 *  Function: Processes reverb effect for block of input samples
 * 
 *  Port of the open-source Freeverb algorithm by Jezar (Dreampoint, 2000)
 *  https://github.com/sinshu/freeverb
 ************************************************************************/
using namespace daisysp;

class Reverb
{
public:

    void init(DaisySeed* seed);
    void setDefaultValues();
    void tick();

    void setAmount(float mix);

    void processBlock(float* input[2], long size);
    void suspend();
    void resume();

private:

    float output[2][BLOCKLENGTH];
    revmodel model;

    BinaryParameterWrapper bypass;
    AudioParameter<float> amount;
    AudioParameter<float> mode;
    AudioParameter<float> size;
    AudioParameter<float> damp;
    AudioParameter<float> width;
};

#endif