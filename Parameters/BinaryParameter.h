#ifndef BINARY_PARAMETER_H
#define BINARY_PARAMETER_H

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

    inline void init(dsy_gpio_pin pin, float updateRate, std::function<void()> cb)
    {
        btn.Init(pin, updateRate);
        callback = cb;
    }

    inline void tick()
    {
        btn.Debounce();
        value = btn.Pressed();
        if(value)
            callback();
        
        System::Delay(5);
    }

private:

    Switch btn;
    bool value;
    std::function<void()> callback;
};

#endif