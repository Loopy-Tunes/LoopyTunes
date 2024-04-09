#ifndef REVERB_H
#define REVERB_H

#include "../../../Parameters/DefaultValues.h"
#include "../../../Drivers/EncoderDriver.h"
#include "../../../Utils/Constants.h"
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

    void init(EncoderDriver* driver, int trackID);
    void setDefaultValues();

    void setBypass(bool b) { isBypass = b; }
    void setAmount(float mix);

    void processBlock(float* input[2], long size);
    void suspend();
    void resume();

private:

    float output[2][BLOCKLENGTH];
    revmodel model;

    bool isBypass;
    SteppedParameterWrapper amount;
    SteppedParameterWrapper mode;
    SteppedParameterWrapper size;
    SteppedParameterWrapper damp;
    SteppedParameterWrapper width;
};

#endif