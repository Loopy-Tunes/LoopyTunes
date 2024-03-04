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
    size.init(seed, 0, 10000, LINEAR, ChannelIDs::ENCODER, [this] (size_t s) { setDelay(s); }); 
    bounce.param.init(seed, 0, 1, LINEAR, ChannelIDs::ENCODER, [this] (float b) { setBounce(b); }); 
    amount.param.init(seed, 0, 1, LINEAR, ChannelIDs::ENCODER, [this] (float a) { setAmount(a); }); 

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

void Delay::prepare()
{
    

}

void Delay::processBlock(float* input[2], size_t size, size_t readPos)
{
    if(bypass.value)
        return;

    for(size_t i = readPos ; i < readPos + size ; i++)
    {
        for(uint_fast8_t j = 0 ; j < 2 ; j++)
        {
            float delay_b = delayLine[j]->Read();
            float delay_o = input[j][i] + (delay_b * amount.value);
            input[j][i] = delay_o;
            float delay_n = input[j][i] + (delay_o * bounce.value);
            delayLine[j]->Write(delay_n);
        }
    }
}