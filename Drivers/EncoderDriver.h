#ifndef ENCODERDRIVER_H
#define ENMCODERRIVER_H

#include "../Parameters/SteppedParameter.h"

/*****************************************************************************//**
 *  Class name: EncoderDriver
 *  Function: Driver for the encoder input, controls the value of FX parameters
 * 
 *  Based off of Encoder class from libDaisy (Stephen Hensley, 2019)
 *  https://github.com/electro-smith/libDaisy/blob/master/src/hid/encoder.h
 ********************************************************************************/

class SteppedParameter;
class EncoderDriver
{
public:

    void init(dsy_gpio_pin button, dsy_gpio_pin a, dsy_gpio_pin b)
    {
        // init gpio

        state = DISARMED;
        prevUpdate = System::GetNow();
        isUpdated = false;
        currentParam = 0;
        valueA = 0;
        valueB = 0;
    }

    void tick()
    {
        now = System::GetNow();

        if(now - prevUpdate >= 1)
        {
            prevUpdate = now;

            // Shift Button states to debounce
            valueA = (valueA << 1) | dsy_gpio_read(&channelA);
            valueB = (valueB << 1) | dsy_gpio_read(&channelB);

            if((valueA & 0x03) == 0x02 && (valueB & 0x03) == 0x00)
            {
                parameters[currentParam]->increment();
            }
            else if((valueB & 0x03) == 0x02 && (valueA & 0x03) == 0x00)
            {
                parameters[currentParam]->decrement();
            }
        }

        btn.Debounce();
    }

    void changeState()
    {
        switch (state)
        {
            case DISARMED:
                state = ARMED;
            break;
            case ARMED:
                state = DISARMED;
            break;
        }
    }

    void setCurrentParam(std::string newParam)
    { 
        for(unsigned int i = 0 ; i < parameters.size() ; i++)
        {
            if(parameters[i]->getID() == newParam)
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

private:

    enum EncoderState
    {
        DISARMED,
        ARMED
    } state;

    bool isUpdated;
    uint32_t prevUpdate;
    uint32_t now;

    int currentParam;
    std::vector<SteppedParameter*> parameters;

    Switch btn;
    dsy_gpio channelA;
    dsy_gpio channelB;

    uint8_t valueA;
    uint8_t valueB;
};

#endif