#include "Delay.h"

using namespace daisysp;

void Delay::init(DaisySeed* seed, DelayLine<float, MAXDELAY>* dl[2])
{
    for(uint_fast8_t i = 0 ; i < 2 ; i++)
    {
        delayLine[i] = dl[i];
        delayLine[i]->Init();
        delayLine[i]->Reset();
    }

    //bypass.param.init(seed, 0, 1, LINEAR, ChannelIDs::TEMP1, [this] (int b) { setBypass(b); }); // to be set to encoder
    amount.param.init(seed, 0, 1, LINEAR, ChannelIDs::AMP4, [this] (float a) { setAmount(a); }); 
    size.init(seed, 0, 10000, LINEAR, ChannelIDs::AMP2, [this] (size_t s) { setDelay(s); }); 
    feedback.param.init(seed, 0, 1, LINEAR, ChannelIDs::AMP3, [this] (float f) { setFeedback(f); }); 

    setDefaultValues();
}

void Delay::setDefaultValues()
{
    bypass.value = delayDefs.bypass;
    amount.value = delayDefs.amount;
    setDelay(delayDefs.size);
    feedback.value = delayDefs.feedback;
}

void Delay::tick()
{
    bypass.param.tick();
    amount.param.tick();
    size.tick();
    feedback.param.tick();
}

void Delay::processBlock(float* buffer[2], size_t size)
{
    if(bypass.value)
        return;

    for(size_t i = 0 ; i < size ; i++)
    {
        for(uint_fast8_t j = 0 ; j < 2 ; j++)
        {
            float delayB = delayLine[j]->Read();
            float delayO = buffer[j][i] + (delayB * amount.value);
            buffer[j][i] = delayO;
            float delayN = buffer[j][i] + (delayO * feedback.value);
            delayLine[j]->Write(delayN);
        }
    }
}