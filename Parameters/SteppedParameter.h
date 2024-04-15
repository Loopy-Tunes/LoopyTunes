#ifndef STEPPEDPARAMETER_H
#define STEPPEDPARAMETER_H

#include "daisy_seed.h"
#include "daisysp.h"
#include "ParameterIDs.h"
#include <string>

/***********************************************************************************//**
 *  Class name: SteppedParameter
 *  Function: Parameter object for DSP classes that contains encoder boilerplate code
 **************************************************************************************/

using namespace daisy;

class SteppedParameter
{
public:

    void init(float mi, float ma, float st, int param, int track, std::function<void(float)> cb)
    {
        paramID = param + track;

        min = mi;
        max = ma;
        step = st;

        callback = cb;
    }

    void increment()
    { 
        if(curVal >= max)
            curVal = max;
        else
            curVal += step;

        callback(curVal); 
    }

    void decrement()
    { 
        if(curVal <= min)
            curVal = min;
        else
            curVal -= step;

        callback(curVal); 
    }

    int getID() { return paramID; }
    float getMin() { return min; }
    float getMax() { return max; }

private:

    int paramID;
    float min;
    float max;
    volatile float curVal;
    float step;

    std::function<void(float)> callback;
};

struct SteppedParameterWrapper
{
    SteppedParameter param;
    float value;
};

#endif