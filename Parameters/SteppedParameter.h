#ifndef STEPPEDPARAMETER_H
#define STEPPEDPARAMETER_H

#include "daisy_seed.h"
#include "daisysp.h"
#include "../Drivers/EncoderDriver.h"
#include "../Utils/Helpers.h"
#include "../Utils/Constants.h"
#include <string>

/***********************************************************************************//**
 *  Class name: SteppedParameter
 *  Function: Parameter object for DSP classes that contains encoder boilerplate code
 **************************************************************************************/

using namespace daisy;

class SteppedParameter
{
public:

    void init(EncoderDriver* driver, float mi, float ma, float st, std::string paramType, std::string track)
    {
        ID = paramType + track;

        min = mi;
        max = ma;
        step = st;

        driver->addParameter(this);
    }

    void increment(){ callback(step); }
    void decrement(){ callback(-step); }

    std::string getID() { return ID; }
    float getMin() { return min; }
    float getMax() { return max; }

private:

    std::string ID;
    float min;
    float max;
    float step;

    std::function<void(float)> callback;
};

struct SteppedParameterWrapper
{
    SteppedParameter param;
    float value;
};

#endif