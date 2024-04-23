#include "Delay.h"

using namespace daisysp;

void Delay::init(EncoderDriver* driver, int trackID, DelayLine<float, MAXDELAY>* dl[2])
{
    for(uint_fast8_t i = 0 ; i < 2 ; i++)
    {
        delayLine[i] = dl[i];
        delayLine[i]->Init();
        delayLine[i]->Reset();
    }

    amount.param.init(0, 1, 0.05, ParameterIDs::Delay::amount, trackID, [this] (float a) { setAmount(a); });
    size.param.init(0, 10000, 10, ParameterIDs::Delay::size, trackID, [this] (float s) { setDelay(toSize(s)); });
    feedback.param.init(0, 1, 0.05, ParameterIDs::Delay::feedback, trackID, [this] (float f) {setFeedback(f); });

    driver->addBypassCallback([this] { setBypass(); });
    driver->addParameter(&amount.param);
    driver->addParameter(&size.param);
    driver->addParameter(&feedback.param);

    setDefaultValues();
}

void Delay::setDefaultValues()
{
    isBypass = true;
    setAmount(delayDefs.amount);
    setDelay(delayDefs.size);
    setFeedback(delayDefs.feedback);
}

void Delay::processBlock(float* input[2], size_t size)
{
    if(isBypass)
        return;

    for(size_t i = 0 ; i < size ; i++)
    {
        for(uint_fast8_t j = 0 ; j < 2 ; j++)
        {
            float delayB = delayLine[j]->Read();
            float delayO = input[j][i] + (delayB * amount.value);
            input[j][i] = delayO;
            float delayN = input[j][i] + (delayO * feedback.value);
            delayLine[j]->Write(delayN);
        }
    }
}