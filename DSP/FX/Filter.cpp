#include "Filter.h"

void Filter::init(EncoderDriver* driver, int trackID)
{
    //filter.Init(48000);
    
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

void Filter::setDefaultValues()
{

}

void Filter::setMode(float m)
{
    if(m == 0)
        filterMode = LOWPASS;
    else
        filterMode = HIGHPASS;
}

void Filter::processBlock(float* buffer[2], size_t size)
{
   if(bypass.value == 1)
        return;

    for(size_t i = 0 ; i < size ; i++)
    {
        for(u_int8_t j = 0 ; j < 2 ; j++)
        {
            //filter.Process(buffer[j][i]);

            switch(filterMode)
            {
                case LOWPASS:
                //buffer[j][i] = filter.Low();
                break;
                case HIGHPASS:
                    //buffer[j][i] = filter.High();
                break;
            }
        }
    }
}