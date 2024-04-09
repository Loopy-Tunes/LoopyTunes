#include "Filter.h"

void Filter::init(EncoderDriver* driver, int trackID)
{
    filter.Init(48000);
    
    hpMin = 200000.f;
    hpMax = 20.f;

    lpMin = 20.f;
    lpMax = 200000.f;

    mode.init(0, 1, 1, ParameterIDs::Filter::mode, trackID, [this] (float m) { setMode(m); });
    freq.init(0, 1, 0.05, ParameterIDs::Filter::frequency, trackID, [this] (float f) {scaleFreq(f); });
    reso.init(0, 1, 0.05, ParameterIDs::Filter::resonance, trackID, [this] (float r) { setReso(r); });

    driver->addParameter(&mode);
    driver->addParameter(&freq);
    driver->addParameter(&reso);

    setDefaultValues();

    // testing  
    isBypass = false;
}

void Filter::setDefaultValues()
{
    setBypass(filterDefs.bypass);
    setMode(filterDefs.mode);
    scaleFreq(filterDefs.frequency);
    setReso(filterDefs.resonance);
}

void Filter::scaleFreq(float f)
{
    float cf = 0;

    switch(filterMode)
    {
        case LOWPASS:
            cf = (((f - 0.f) * (lpMax - lpMin)) / (1.f - 0.f)) + lpMin;
        break;
        case HIGHPASS:
            cf = (((f - 0.f) * (hpMax - hpMin)) / (1.f - 0.f)) + hpMin;
        break;
    }

    setFreq(cf);
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
   if(isBypass)
        return;

    for(size_t i = 0 ; i < size ; i++)
    {
        for(u_int8_t j = 0 ; j < 2 ; j++)
        {
            filter.Process(buffer[j][i]);

            switch(filterMode)
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