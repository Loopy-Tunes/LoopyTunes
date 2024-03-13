#ifndef ENCODERDRIVER_H
#define ENMCODERRIVER_H

#include "Parameters/SteppedParameter.h"

class EncoderDriver
{
public:

    void init()
    {
        // init gpio
    }

    void tick()
    {

    }

    void debounce()
    {
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
        }
    }

    void setParameter(std::string newParam)
    { 
        for(int i = 0 ; i < parameters.size() ; i++)
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

    int currentParam;
    std::vector<SteppedParameter*> parameters;

    Switch btn;
    dsy_gpio inc;
    dsy_gpio dec;

    bool isArmed;
};

#endif