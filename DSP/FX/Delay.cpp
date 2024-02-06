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

    bypassParam.init(seed, 0, 1, LINEAR, ChannelIDs::Encoder, [this] (int b) { setBypass(b); });
    sizeParam.init(seed, 0, 10000, LINEAR, ChannelIDs::Encoder, [this] (size_t s) { setDelay(s); });
    bounceParam.init(seed, 0, 1, LINEAR, ChannelIDs::Encoder, [this] (float b) { setBounce(b); });
    amountParam.init(seed, 0, 1, LINEAR, ChannelIDs::Encoder, [this] (float a) { setAmount(a); });

    bypass = 0;
    size = 0;
    bounce = 0;
    amount = 0;
}

void Delay::tick()
{
    bypassParam.tick();
    sizeParam.tick();
    bounceParam.tick();
    amountParam.tick();
}

void Delay::prepare()
{
    

}

void Delay::processBlock(float* input[2], size_t size, size_t rp)
{
    if(bypass == 0)
        return;

    for(size_t i = rp ; i < rp + size ; i++)
    {
        for(int j = 0 ; j < 2 ; j++)
        {
            float delay_b = delayLine[j]->Read();
            float delay_o = input[j][i] + (delay_b * amount);
            input[j][i] = delay_o;
            float delay_n = input[j][i] + (delay_o * bounce);
            delayLine[j]->Write(delay_n);
        }
    }
}