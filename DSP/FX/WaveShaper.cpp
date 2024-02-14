#include "WaveShaper.h"

using namespace daisysp;

void WaveShaper::init(DaisySeed* seed)
{
    bypass.param.init(seed, 0, 1, LINEAR, ChannelIDs::TEMP1, [this] (int b) { setBypass(b); }); // to be set to encoder
    input.param.init(seed, 0, 1, LINEAR, ChannelIDs::TEMP3, [this] (float i) { setInput(i); }); // to be set to encoder
    waveShape.param.init(seed, 0, 1, LINEAR, ChannelIDs::TEMP4, [this] (float ws) { setWaveShape(ws); }); // to be set to encoder

    bypass.value = 0;
    input.value = 0;
    waveShape.value = 0;

    gain = 0;
}

void WaveShaper::tick()
{
    bypass.param.tick();
    input.param.tick();
    waveShape.param.tick();
}

void WaveShaper::prepare()
{

}

void WaveShaper::calculateAutoGain()
{

}

void WaveShaper::process()
{

}