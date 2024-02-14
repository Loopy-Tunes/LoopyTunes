#include "Waveshaper.h"

using namespace daisysp;

void Waveshaper::init(DaisySeed* seed)
{
    bypass.param.init(seed, 0, 1, LINEAR, ChannelIDs::TEMP1, [this] (int b) { setBypass(b); }); // to be set to encoder
    input.param.init(seed, 0, 1, LINEAR, ChannelIDs::TEMP2, [this] (float i) { setInput(i); }); // to be set to encoder
    waveshape.param.init(seed, 0, 3, LINEAR, ChannelIDs::TEMP3, [this] (int ws) { setWaveshape(ws); }); // to be set to encoder
    amount.param.init(seed, 0, 1, LINEAR, ChannelIDs::TEMP4, [this] (float a) { setAmount(a); }); // to be set to encoder

    bypass.value = 0;
    input.value = 0;
    waveshape.value = 0;
    amount.value = 0;

    gain = 0;
}

void Waveshaper::tick()
{
    bypass.param.tick();
    input.param.tick();
    waveshape.param.tick();
}

void Waveshaper::prepare()
{

}

void Waveshaper::calculateAutoGain()
{

}

void Waveshaper::processBlock(float* input[2], size_t size, size_t readPos)
{
    if(bypass.value == 0)
        return;

    // handle input gain
    
    switch(waveshape.value)
    {
        case SINE:
            processSine(input, size, readPos);
        break;
        case TANH:
            processTanh(input, size, readPos);
        break;
        case SIGNUM:
            processSignum(input, size, readPos);
        break;
    }
}

void Waveshaper::processSine(float* input[2], size_t size, size_t readPos)
{
    for(size_t i = readPos ; i < readPos + size ; i++)
    {
        for(uint_fast8_t j = 0 ; j < 2 ; j++)
        {
            float output = cos(input[i][j]);
            input[i][j] = (1.f - amount.value) * input[i][j] + output * amount.value;
        }
    }
}

void Waveshaper::processTanh(float* input[2], size_t size, size_t readPos)
{
    for(size_t i = readPos ; i < readPos + size ; i++)
    {
        for(uint_fast8_t j = 0 ; j < 2 ; j++)
        {
            float output = tanh(input[j][i]);
            input[i][j] = (1.f - amount.value) * input[i][j] + output * amount.value;
        }
    }
}

void Waveshaper::processSignum(float* input[2], size_t size, size_t readPos)
{
    for(size_t i = readPos ; i < readPos + size ; i++)
    {
        for(uint_fast8_t j = 0 ; j < 2 ; j++)
        {
            
        }
    }
}