#ifndef BINARYPARAMETER_H
#define BINARYPARAMETER_H

#include "daisy_seed.h"
#include <functional>

/*****************************************************************************//**
 *  Class name: BinaryParameter
 *  Function: Parameter object that contains boilerplate code for button inputs
 ********************************************************************************/

using namespace daisy;

class BinaryParameter
{
public:

    /*****************************************************************//**
    * @brief Initialises an instance of the class
    * @param pin The Daisy Seed pin the instance is assigned to
    * @param updateRate The rate at which the button is updated
    * @param cb The callback function executed when the button is pressed
    *********************************************************************/
    inline void init(dsy_gpio_pin pin, float updateRate, std::function<void()> cb)
    {
        btn.Init(pin, updateRate);
        callback = cb;
    }

    /**********************************************************//**
    * @brief Checks to see if the button has been pressed
    *************************************************************/
    inline void tick()
    {
        btn.Debounce();
        if(btn.FallingEdge())
            callback();
    }
    
    /**********************************************************//**
    * @brief Checks the state of the button
    * @return If the button is pressed or not
    *************************************************************/
    bool isPressed() { return btn.Pressed(); }

private:

    Switch btn;
    std::function<void()> callback;
};

struct BinaryParameterWrapper
{
    BinaryParameter param;
    bool value;
};
#endif