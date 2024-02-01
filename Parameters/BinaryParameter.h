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

    void init(dsy_gpio_pin pin, float updateRate, std::function<void()> cb)
    {
        btn.Init(pin, updateRate);
        callback = cb;
    }

    void tick()
    {
        value = btn.Pressed();
        if(value)
            callback();

        btn.Debounce();
    }

private:

    Switch btn;
    bool value;
    std::function<void()> callback;
};

#endif