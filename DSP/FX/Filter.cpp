#include "Filter.h"

void Filter::init(EncoderDriver* driver, int trackID)
{
    filter.Init();

    mode.init(0, 1, 1, ParameterIDs::Filter::mode, trackID, [this] (float m) { setMode(m); });
    freq.init(0, 0.490, 0.01, ParameterIDs::Filter::frequency, trackID, [this] (float f) { setFreq(f); });

    driver->addBypassCallback([this] { setBypass(); });
    driver->addParameter(&mode);
    driver->addParameter(&freq);

    setDefaultValues();
}

void Filter::setDefaultValues()
{
    isBypass = true;
    setMode(filterDefs.mode);
    setFreq(filterDefs.frequency);
}

void Filter::setMode(float m)
{
    if(m == 0)
        filter.SetFilterMode(daisysp::OnePole::FilterMode::FILTER_MODE_LOW_PASS);
    else
        filter.SetFilterMode(daisysp::OnePole::FilterMode::FILTER_MODE_HIGH_PASS);
}

void Filter::processBlock(float* input[2], size_t size)
{
   if(isBypass)
        return;

    for(size_t i = 0 ; i < size ; i++)
    {
        filter.ProcessBlock(input[L], size);
        filter.ProcessBlock(input[R], size);
    }
}