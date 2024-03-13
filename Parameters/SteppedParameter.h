#ifndef STEPPEDPARAMETER_H
#define STEPPEDPARAMETER_H

#include "daisy_seed.h"
#include "daisysp.h"
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

    void init(float mi, float ma, float st, std::string paramType, std::string track)
    {
        ID = std::strcat(paramType, track);

        min = mi;
        max = ma;
        step = st;

        // add pointer to class instance to parameter vector in encoder driver
    }

    void increment(){ callback(step); }
    void decrement(){ callback(-step); }

    std::string getID() { return ID; }
    float getMin() { return min; }
    float getMax() { return max; }

private:

    // pointer to driver

    std::string ID;
    float min;
    float max;
    float step;

    std::function<void()> callback;
};

struct SteppedParameterWrapper
{
    SteppedParameter param;
    float value;
};

#endif