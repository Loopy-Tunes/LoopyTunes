#include "Waveshaper.h"

using namespace daisysp;

void Waveshaper::init(DaisySeed* seed)
{
    //bypass.param.init(daisy::seed::D5, 1000, [this]{ setBypass(); }); // CHECK THIS
    amount.param.init(seed, 0, 1, LINEAR, ChannelIDs::AMP3, [this] (float a) { setAmount(a); }); // to be set to encoder
    input.param.init(seed, 0, 1, LINEAR, ChannelIDs::AMP4, [this] (float i) { setInput(i); }); // to be set to encoder
    waveshape.param.init(seed, 0, 3, LINEAR, ChannelIDs::AMP2, [this] (int ws) { setWaveshape(ws); }); // to be set to encoder

    setDefaultValues();
}

 void Waveshaper::setDefaultValues()
 {
    bypass.value = waveshaperDefs.bypass;
    amount.value = waveshaperDefs.amount;
    input.value = waveshaperDefs.input;
    waveshape.value = waveshaperDefs.waveshape;

    gain = 0;
 }

void Waveshaper::tick()
{
    bypass.param.tick();
    amount.param.tick();
    input.param.tick();
    waveshape.param.tick();
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