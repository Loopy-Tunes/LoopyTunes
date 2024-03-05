#ifndef REVERB_H
#define REVERB_H

#include "../../../Parameters/AudioParameter.h"
#include "../../../Parameters/BinaryParameter.h"
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
    void tick();

    void processBlock(float* input[2], long size);
    void processBlockReplacing(float* input[2], float* output[2], long size, size_t readPos);
    void suspend();
    void resume();

private:

    float output[2][BLOCKLENGTH];
    revmodel model;

    BinaryParameterWrapper bypass;
    AudioParameter<float> mode;
    AudioParameter<float> size;
    AudioParameter<float> damp;
    AudioParameter<float> wet;
    AudioParameter<float> dry;
    AudioParameter<float> width;
};

#endif