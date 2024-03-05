#include "Waveshaper.h"

using namespace daisysp;

void Waveshaper::init(DaisySeed* seed)
{
    bypass.param.init(daisy::seed::D5, 1000, [this]{ setBypass(); }); // CHECK THIS
    input.param.init(seed, 0, 1, LINEAR, ChannelIDs::ENCODER, [this] (float i) { setInput(i); }); // to be set to encoder
    waveshape.param.init(seed, 0, 3, LINEAR, ChannelIDs::ENCODER, [this] (int ws) { setWaveshape(ws); }); // to be set to encoder
    amount.param.init(seed, 0, 1, LINEAR, ChannelIDs::ENCODER, [this] (float a) { setAmount(a); }); // to be set to encoder

    bypass.value = true;
    input.value = 0;
    waveshape.value = 1;
    amount.value = 1;

    gain = 0;
}

void Waveshaper::tick()
{
    bypass.param.tick();
    input.param.tick();
    waveshape.param.tick();
    amount.param.tick();
}

void Waveshaper::prepare()
{

}

void Waveshaper::calculateAutoGain()
{

}

void Waveshaper::processBlock(float* buffer[2], size_t size)
{
    if(bypass.value)
        return;

    for(size_t i = 0 ; i < BLOCKLENGTH ; i++)
    {
        for(uint_fast8_t j = 0 ; j < 2 ; j++)
        {
            //input[i][j] = input[i][j] * input.value;
        }
    }
    
    switch(waveshape.value)
    {
        case SINE:
            processSine(buffer, size);
        break;
        case TANH:
            processTanh(buffer, size);
        break;
        case SIGNUM:
            processSignum(buffer, size);
        break;
    }
}

void Waveshaper::processSine(float* buffer[2], size_t size)
{
    for(size_t i = 0 ; i < size ; i++)
    {
        for(uint_fast8_t j = 0 ; j < 2 ; j++)
        {
            float output = cos(buffer[j][i]);
            buffer[j][i] = (1.f - amount.value) * buffer[j][i] + output * amount.value;
        }
    }
}

void Waveshaper::processTanh(float* buffer[2], size_t size)
{
    for(size_t i = 0 ; i < size ; i++)
    {
        for(uint_fast8_t j = 0 ; j < 2 ; j++)
        {
            float output = tanh(buffer[j][i]);
            buffer[j][i] = (1.f - amount.value) * buffer[j][i] + output * amount.value;
        }
    }
}

void Waveshaper::processSignum(float* buffer[2], size_t size)
{
    for(size_t i = 0 ; i < size ; i++)
    {
        for(uint_fast8_t j = 0 ; j < 2 ; j++)
        {
            float output = (0 < buffer[j][i]) - (buffer[j][i] < 0);
            buffer[j][i] = (1.f - amount.value) * buffer[j][i] + output * amount.value;
        }
    }
}