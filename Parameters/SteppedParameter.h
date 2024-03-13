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

template<class type>
class SteppedParameter
{
public:

    void init(type mi, type ma, type st, std::string paramType, std::string track)
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
    type getMin() { return min; }
    type getMax() { return max; }

private:

    // pointer to driver

    std::string ID;
    type min;
    type max;
    type step;

    std::function<void()> callback;
};

template<class type>
struct SteppedParameterWrapper
{
    SteppedParameter<type> param;
    type value;
};

#endif