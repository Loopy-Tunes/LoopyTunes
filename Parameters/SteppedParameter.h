#ifndef STEPPEDPARAMETER_H
#define STEPPEDPARAMETER_H

#include "daisy_seed.h"
#include "daisysp.h"
#include "ParameterIDs.h"
#include <string>
#include <functional>

/***********************************************************************************//**
 *  Class name: SteppedParameter
 *  Function: Parameter object for DSP classes that contains encoder boilerplate code
 **************************************************************************************/

using namespace daisy;

class SteppedParameter
{
public:

    /*****************************************************************//**
    * @brief Initialises an instance of the class
    * @param mi The lowest value the instance should decrement to
    * @param ma The highest value the instance should increment to
    * @param st The value the instance should increment/decrement by
    * @param param The ID of the parameters the instance is assigned to
    * @param track The ID of the track the instance is assigned to
    * @param cb The callback function executed when the value changes
    ********************************************************************/
    void init(float mi, float ma, float st, int param, int track, std::function<void(float)> cb)
    {
        paramID = param + track;

        min = mi;
        max = ma;
        step = st;

        callback = cb;
    }
    
    /***************************************************************//**
    * @brief Increments the instance's value and executes the callback
    *******************************************************************/
    void increment()
    { 
        if(curVal >= max)
            curVal = max;
        else
            curVal += step;

        callback(curVal); 
    }

    /***************************************************************//**
    * @brief Decrements the instance's value and executes the callback
    *******************************************************************/
    void decrement()
    { 
        if(curVal <= min)
            curVal = min;
        else
            curVal -= step;

        callback(curVal); 
    }

    /***************************************************************//**
    * @brief Fetches the instance's full ID
    * @return The ID of the instance
    *******************************************************************/
    int getID() { return paramID; }

    /***************************************************************//**
    * @brief Fetches the lowest value the instance decrements to
    * @return The miminum value
    *******************************************************************/
    float getMin() { return min; }

    /***************************************************************//**
    * @brief Fetches the highest value the instance increments to
    * @return The maximum value
    *******************************************************************/
    float getMax() { return max; }

    /***************************************************************//**
    * @brief Fetches the current value of the instance
    * @return The current value
    *******************************************************************/
    float getCurVal() { return curVal; }

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