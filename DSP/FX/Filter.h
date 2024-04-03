#ifndef FILTER_H
#define FILTER_H

#include "../../Parameters/DefaultValues.h"
#include "../../Drivers/EncoderDriver.h"
#include "../../Utils/Constants.h"

/**********************************************************************************************//**
 *  Class name: Filter
 *  Function: Wrapper for DaisySP ladder filter class that applies a filter to a block of samples
 *************************************************************************************************/
using namespace daisysp;

class Filter
{
public:

    void init(EncoderDriver* driver, int trackID)
    {
        filter.Init(48000);
        
        bypass.param.init(0, 1, 1, ParameterIDs::Filter::bypass, trackID, [this] (float b) { setBypass(b); });
        freq.init(0, 1, 0.05, ParameterIDs::Filter::frequency, trackID, [this] (float f) {setFreq(f); });
        reso.init(0, 1, 0.05, ParameterIDs::Filter::resonance, trackID, [this] (float r) { setReso(r); });
        mode.init(0, 1, 1, ParameterIDs::Filter::mode, trackID, [this] (float m) { setMode(m); });

        //driver->addParameter(&bypass.param);
        //driver->addParameter(&freq);
        //driver->addParameter(&reso);
        //driver->addParameter(&mode);

        setDefaultValues();
    }

    void setDefaultValues()
    {

    }

    void setBypass(float b) { bypass.value = b; }
    void setFreq(float f) { filter.SetFreq(f); }
    void setReso(float r) { filter.SetRes(r); }

    void setMode(float m)
    {
        if(m == 0)
            state = LOWPASS;
        else
            state = HIGHPASS;
    }

    void processBlock(float* buffer[2], size_t size)
    {
        if(bypass.value == 1)
            return;

        for(size_t i = 0 ; i < size ; i++)
        {
            for(u_int8_t j = 0 ; j < 2 ; j++)
            {
                filter.Process(buffer[j][i]);

                switch(state)
                {
                case LOWPASS:
                    buffer[j][i] = filter.Low();
                    break;
                case HIGHPASS:
                    buffer[j][i] = filter.High();
                    break;
                }
            }
        }
    }

private:

    enum State
    {
        LOWPASS = 0,
        HIGHPASS
    } state;

    Svf filter;
    SteppedParameterWrapper bypass;
    SteppedParameter freq;
    SteppedParameter reso;
    SteppedParameter mode;
};

#endif