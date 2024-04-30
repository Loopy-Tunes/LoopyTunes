#ifndef AUDIOPARAMETER_H
#define AUDIOPARAMETER_H

#include "daisy_seed.h"
#include "daisysp.h"
#include "../Utils/Helpers.h"
#include "../Utils/Constants.h"
#include <cstdint>
#include <functional>
#include <memory>
#include <type_traits>

/*****************************************************************************//**
 *  Class name: AudioParameter
 *  Function: Parameter object for DSP classes that contains pot boilerplate code
 ********************************************************************************/

using namespace daisy;

template <class type>
class AudioParameter
{
public:

    /**************************************************************************************//**
    * @brief Initialises an instance of the class
    * @param seed A pointer to the program's instance of the hardware
    * @param mi The minimum value the parameter's input should be scaled too
    * @param ma The maximum value the parameter's input should be scaled too
    * @param c The type of curve that should be used to scale the input
    * @param ID The channel ID for the ADC channel the instance is assigned too
    * @param cb The callback function that should be executed when the input values changes
    ******************************************************************************************/
    void init(DaisySeed* seed, type mi, type ma, CurveType c, int ID, std::function<void(type)> cb)
    {
        hw = seed;
        input = 0;

        curVal = 0;
        min = mi;
        max = ma;

        curve = c;
        channelID = ID;
        callback = cb;
    }
    
    /*******************************************************************//**
    * @brief Handles the polling of the assigned ADC channel
    ***********************************************************************/
    inline void tick() 
    {
        float newInput = hw->adc.GetFloat(channelID);
        if(newInput > (input + jitter) || newInput < (input - jitter))
        {
            input = newInput;
            processCurve();
            callback(curVal);
        }
    }

    /***************************************************************************//**
    * @brief Scales the input value according to the assigned curve
    *******************************************************************************/
    void processCurve()
    {
        switch(curve)
        {
            case LINEAR:
                curVal = ((input / 1.0f) * (max - min)) + min;
            break;
            case EXP:
                curVal = ((input * input) * (max - min)) + min;
            break;
        }
    }

    /**********************************************************//**
    * @brief Fetches the current value of the instance
    * @return the current value
    *************************************************************/
    inline type getValue() { return curVal; }
    
private:

    DaisySeed* hw;
    float input;
    const float jitter = 0.01f;

    type curVal, min, max;
    int channelID;
    CurveType curve;

    std::function<void(type)> callback;
};

template <class type>
struct AudioParameterWrapper
{
    AudioParameter<type> param;
    type value;
};

#endif