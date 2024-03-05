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

    inline void init(dsy_gpio_pin pin, float updateRate, std::function<void()> cb)
    {
        btn.Init(pin, updateRate);
        callback = cb;
    }

    inline void tick()
    {
        btn.Debounce();
        if(btn.FallingEdge())
            callback();
    }

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