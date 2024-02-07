#include "Delay.h"

using namespace daisysp;

void Delay::init(DaisySeed* seed, DelayLine<float, MAXDELAY>* dl[2])
{
    for(int i = 0 ; i < 2 ; i++)
    {
        delayLine[i] = dl[i];
        delayLine[i]->Init();
        delayLine[i]->Reset();
    }

    bypass.param.init(seed, 0, 1, LINEAR, ChannelIDs::TEMP1, [this] (int b) { setBypass(b); }); // to be set to encoder
    size.init(seed, 0, 10000, LINEAR, ChannelIDs::TEMP2, [this] (size_t s) { setDelay(s); }); // to be set to encode
    bounce.param.init(seed, 0, 1, LINEAR, ChannelIDs::Amp1, [this] (float b) { setBounce(b); }); // to be set to encoder
    amount.param.init(seed, 0, 1, LINEAR, ChannelIDs::TEMP4, [this] (float a) { setAmount(a); }); // to be set to encoder

    bypass.value = 0;
    bounce.value = 0;
    amount.value = 0;
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

void Delay::processBlock(float* input[2], size_t size, size_t rp)
{
    if(bypass.value == 0)
        return;

    for(size_t i = rp ; i < rp + size ; i++)
    {
        for(int j = 0 ; j < 2 ; j++)
        {
            float delay_b = delayLine[j]->Read();
            float delay_o = input[j][i] + (delay_b * amount.value);
            input[j][i] = delay_o;
            float delay_n = input[j][i] + (delay_o * bounce.value);
            delayLine[j]->Write(delay_n);
        }
    }
}