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
    size.init(seed, 0, 10000, LINEAR, ChannelIDs::AMP2, [this] (size_t s) { setDelay(s); }); 
    bounce.param.init(seed, 0, 1, LINEAR, ChannelIDs::AMP3, [this] (float b) { setBounce(b); }); 
    amount.param.init(seed, 0, 1, LINEAR, ChannelIDs::AMP4, [this] (float a) { setAmount(a); }); 

    bypass.value = false; // set to 0 when pots working
    bounce.value = 0.8;
    amount.value = 0.5;
    setDelay(40000);
}

void Delay::tick()
{
    bypass.param.tick();
    size.tick();
    bounce.param.tick();
    amount.param.tick();
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
            float delayN = buffer[j][i] + (delayO * bounce.value);
            delayLine[j]->Write(delayN);
        }
    }
}