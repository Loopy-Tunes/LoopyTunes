#ifndef REVERB_H
#define REVERB_H

#include "../../../Parameters/AudioParameter.h"
#include "../../../Parameters/BinaryParameter.h"
#include "revmodel.hpp"

/*********************************************************************//**
 *  Class name: Reverb
 *  Function: Processes reverb effect for block of input sanples
 * 
 *  Port of the open-source Freeverb algorithm by Jezar (Dreampoint, 2000)
 *  https://github.com/sinshu/freeverb
 ************************************************************************/
using namespace daisysp;

class Reverb
{
public:

    void init(DaisySeed* seed);
    void process();
    void processReplacing();
    void suspend();
    void resume();

private:

    revmodel model;

    BinaryParameterWrapper bypass;
    AudioParameterWrapper<float> mode;
    AudioParameterWrapper<float> size;
    AudioParameter<float> damp;
    AudioParameter<float> wet;
    AudioParameter<float> dry;
    AudioParameter<float> width;
};

#endif