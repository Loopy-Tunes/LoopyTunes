#ifndef ENCODERDRIVER_H
#define ENCODERDRIVER_H

#include "../Parameters/SteppedParameter.h"

/*****************************************************************************//**
 *  Class name: EncoderDriver
 *  Function: Driver for the encoder input, controls the value of FX parameters
 * 
 *  Based off of Encoder class from libDaisy (Stephen Hensley, 2019)
 *  https://github.com/electro-smith/libDaisy/blob/master/src/hid/encoder.h
 ********************************************************************************/

class EncoderDriver
{
public:

    void init(dsy_gpio_pin button, dsy_gpio_pin a, dsy_gpio_pin b, std::function<void()> navCb)
    {
        parameters.reserve(70);

        prevUpdate = 0;
        isUpdated = false;

        isNavigation = true;
        navCallback = navCb;

        currentParam = 0;
        valueA = 0xFF;
        valueB = 0xFF;

        btn.Init(button);
        
        channelA.pin = a;
        channelB.pin = b;
        channelA.mode = DSY_GPIO_MODE_INPUT;
        channelB.mode = DSY_GPIO_MODE_INPUT;
        channelA.pull = DSY_GPIO_PULLUP;
        channelB.pull = DSY_GPIO_PULLUP;
        dsy_gpio_init(&channelA);
        dsy_gpio_init(&channelB);

        // FOR TESTING
        currentParam = 3;
    }

    void tick()
    {
        u_int32_t now = System::GetNow();
        if(now - prevUpdate >= 1) // adjust to change update rate, 1 = 1000Hz, 2 = 2000Hz etc.
        {
            prevUpdate = now;

            // Shift Button states to debounce
            valueA = (valueA << 1) | dsy_gpio_read(&channelA);
            valueB = (valueB << 1) | dsy_gpio_read(&channelB);

            if(!isNavigation)
            {
                if((valueA & 0x03) == 0x02 && (valueB & 0x03) == 0x00)
                    parameters[currentParam]->decrement();
                else if((valueB & 0x03) == 0x02 && (valueA & 0x03) == 0x00)
                    parameters[currentParam]->increment();
            }
        }

        btn.Debounce();
        if(btn.Pressed())
            buttonCallback();
    }

    void setIsNavigation(bool isNav)
    {
        isNavigation = isNav;
    }

    void buttonCallback()
    {
        if(isNavigation)
            navCallback();
    }

    bool getButtonState() { return btn.Pressed(); }
    std::function<void()> getBypassCallback(size_t index) { return bypassCallbacks.at(index); }

    void setCurrentParam(int newID)
    { 
        for(unsigned int i = 0 ; i < parameters.size() ; i++)
        {
            if(parameters[i]->getID() == newID)
            {
                currentParam = i;
                break;
            }
        }
    }

    void addParameter(SteppedParameter* newParam)
    {
        parameters.push_back(newParam);
    }

    void addBypassCallback(std::function<void()> newCallback)
    {
        bypassCallbacks.push_back(newCallback);
    }

    SteppedParameter* getParameter(int paramID)
    {
        for(unsigned int i = 0 ; i < parameters.size() ; i++)
        {
            if(parameters[i]->getID() == paramID)
                return parameters[i];
            else
                return nullptr;
        }
    }

private:

    bool isUpdated;
    uint32_t prevUpdate;

    bool isNavigation;
    std::function<void()> navCallback;

    int currentParam;
    std::vector<SteppedParameter*> parameters;
    std::vector<std::function<void()>> bypassCallbacks;

    Switch btn;
    dsy_gpio channelA;
    dsy_gpio channelB;

    uint8_t valueA;
    uint8_t valueB;
};

#endif