#ifndef BYPASSBUTTON_H
#define BYPASSBUTTON_H

#include "../../Drivers/EncoderDriver.h"
#include <functional>

/********************************************************//**
 *  Class name: BypassButton
 *  Function: Button used for bypassing an effect
 ***********************************************************/

class BypassButton 
{
public:

    void init(EncoderDriver* ed, std::function<void()> bypassCallback)
    {
        encoder = ed;

        callback = bypassCallback;
        isSelected = false;
    }

    void tick()
    {
        if(isSelected && encoder->getButtonState())
        {
            callback();
        }
    }

    void repaint()
    {
        if(isSelected)
        {

        } else
        {

        }
    }

    void setIsSelected(bool state) { isSelected = state; } // called when the bypass button is selected

private:

    EncoderDriver* encoder;

    std::function<void()> callback;
    bool isSelected;
};

#endif