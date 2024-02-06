#include "Delay.h"

using namespace daisysp;

DelayLine<float, MAXDELAY> DSY_SDRAM_BSS buffer;

void Delay::init(DaisySeed* seed)
{
    buffer.Init();
    buffer.Reset();

    bypass.init(seed, 0, 1, LINEAR, ChannelIDs::Encoder);
    size.init(seed, 0, 1, LINEAR, ChannelIDs::Encoder);
    bounce.init(seed, 0, 1, LINEAR, ChannelIDs::Encoder);
    amount.init(seed, 0, 1, LINEAR, ChannelIDs::Encoder);
}

void Delay::tick()
{
    bypass.tick();
    size.tick();
    bounce.tick();
    amount.tick();
}

void Delay::prepare()
{
    

}

void Delay::processBlock(float* input[2], size_t size, size_t rp)
{
    if(bypass.getValue() == 0)
        return;

    for(size_t i = rp ; i < rp + size ; i++)
    {
        // read value from delay line
        // calculate output
        // calculate new delay line entry
        // write new delay to delay line
    }
}