#include "Delay.h"

using namespace daisysp;

DelayLine<float, MAXDELAY> DSY_SDRAM_BSS buffer;

void Delay::init(DaisySeed* seed)
{
    buffer.Init();
    buffer.Reset();

    bypassParam.init(seed, 0, 1, LINEAR, ChannelIDs::Encoder, [this] (int b) { setBypass(b); });
    sizeParam.init(seed, 0, 10000, LINEAR, ChannelIDs::Encoder, [this] (size_t s) { setSize(s); });
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
        // read value from delay line
        // calculate output
        // calculate new delay line entry
        // write new delay to delay line
    }
}