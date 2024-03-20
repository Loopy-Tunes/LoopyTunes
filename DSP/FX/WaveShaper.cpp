#include "Waveshaper.h"

using namespace daisysp;

void Waveshaper::init(EncoderDriver* driver, std::string trackID)
{
    bypass.param.init(0, 1, 1, ParameterIDs::Waveshaper::bypass, trackID, [this] (float b) { setBypass(b); });
    amount.param.init(0, 1, 0.05, ParameterIDs::Waveshaper::amount, trackID, [this] (float a) { setAmount(a); });
    inputGain.param.init(0, 1, 0.05, ParameterIDs::Waveshaper::inputGain, trackID, [this] (float i) { setInputGain(i); });
    waveshape.param.init(0, 3, 1, ParameterIDs::Waveshaper::waveshape, trackID, [this] (float ws) { setWaveshape(ws); });

    driver->addParameter(&bypass.param);
    driver->addParameter(&amount.param);
    driver->addParameter(&inputGain.param);
    driver->addParameter(&waveshape.param);

    setDefaultValues(); 

    for(size_t i = 0 ; i < BLOCKLENGTH ; i++)
    {
        for(u_int8_t j = 0 ; j < 2 ; j++)
        {
            inputAG[j][i] = 0;
            outputAG[j][i] = 0; 
            diffAG[j][i] = 0;  
        }
    }
}

 void Waveshaper::setDefaultValues()
 {
    bypass.value = waveshaperDefs.bypass;
    amount.value = waveshaperDefs.amount;
    inputGain.value = waveshaperDefs.input;
    waveshape.value = waveshaperDefs.waveshape;
 }

void Waveshaper::tick()
{

}

inline void Waveshaper::setInputAG(float* buffer[2], size_t size) 
{  
    for(size_t i = 0 ; i < size ; i++)
    {
        for(u_int8_t j = 0 ; j < 2 ; j++)
        {
            //inputAG[j][i] = **buffer[j][i]; 
        }
    }
}

inline void Waveshaper::setOutputAG(float* buffer[2], size_t size) 
{ 
    for(size_t i = 0 ; i < size ; i++)
    {
        for(u_int8_t j = 0 ; j < 2 ; j++)
        {
            //outputAG[j][i] = **buffer[j][i]; 
        }
    } 
}

void Waveshaper::calculateAutoGain(size_t size)
{
    for(size_t i = 0 ; i < size ; i++)
    {
        for(u_int8_t j = 0 ; j < 2 ; j++)
        {
            diffAG[j][i] = outputAG[j][i] - inputAG[j][i];
        }
    }
}

void Waveshaper::applyAutoGain(float* buffer[2], size_t size)
{
    for(size_t i = 0 ; i < size ; i++)
    {
        for(uint_fast8_t j = 0 ; j < 2 ; j++)
        {
            buffer[j][i] -= diffAG[j][i];
        }
    }
}

void Waveshaper::processBlock(float* buffer[2], size_t size)
{
    if(bypass.value == 1)
        return;

    setInputAG(buffer, size);

    for(size_t i = 0 ; i < BLOCKLENGTH ; i++)
    {
        for(uint_fast8_t j = 0 ; j < 2 ; j++)
        {
            buffer[j][i] *= inputGain.value;
        }
    }

    int shape = waveshape.value;
    switch(shape)
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

    setOutputAG(buffer, size);
    calculateAutoGain(size_t size);
    applyAutoGain(buffer, size);
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