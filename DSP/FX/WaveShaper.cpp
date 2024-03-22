#include "Waveshaper.h"

using namespace daisysp;

void Waveshaper::init(EncoderDriver* driver, std::string trackID)
{
    folder.Init();
    lfo.Init(48000);
    lfo.SetWaveform(0);
    lfo.SetAmp(0.5);
    lfo.Reset(0);

    bits = 0;

    bypass.param.init(0, 1, 1, ParameterIDs::Waveshaper::bypass, trackID, [this] (float b) { setBypass(b); });
    amount.param.init(0, 1, 0.05, ParameterIDs::Waveshaper::amount, trackID, [this] (float a) { setAmount(a); });
    funcControl.param.init(0, 1, 0.05, ParameterIDs::Waveshaper::funcControl, trackID, [this] (float fc) { setFuncControl(fc); });
    waveshape.param.init(0, 4, 1, ParameterIDs::Waveshaper::waveshape, trackID, [this] (float ws) { setWaveshape(ws); });

    driver->addParameter(&bypass.param);
    driver->addParameter(&amount.param);
    driver->addParameter(&funcControl.param);
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
    funcControl.value = waveshaperDefs.input;
    waveshape.value = waveshaperDefs.waveshape;
 }

void Waveshaper::tick()
{

}

inline void Waveshaper::scaleControlParam()
{
    int shape = waveshape.value;

    switch(shape)
    {
        case LFO:
            // set lfo frequency
        break;
        case BITREDUCER:
            // set bit reduction value
        break;
    }
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

    int shape = waveshape.value;
    if(shape == CLIPPER || shape == FOLDER)
    {
        for(size_t i = 0 ; i < BLOCKLENGTH ; i++)
        {
            for(uint_fast8_t j = 0 ; j < 2 ; j++)
            {
                buffer[j][i] *= funcControl.value;
            }
        }
    }

    switch(shape)
    {
        case CLIPPER:
            processClipper(buffer, size);
        break;
        case FOLDER:
            processFolder(buffer, size);
        break;
        case LFO:
            processLFO(buffer, size);
        break;
        case BITREDUCER:
            processBitReducer(buffer, size);
        break;
    }

    if(shape == CLIPPER || shape == FOLDER)
    {
        setOutputAG(buffer, size);
        calculateAutoGain(size);
        applyAutoGain(buffer, size);
    }
}

void Waveshaper::processClipper(float* buffer[2], size_t size)
{
    for(size_t i = 0 ; i < size ; i++)
    {
        for(uint_fast8_t j = 0 ; j < 2 ; j++)
        {
            
        }
    }
} 

void Waveshaper::processFolder(float* buffer[2], size_t size)
{
    for(size_t i = 0 ; i < size ; i++)
    {
        for(uint_fast8_t j = 0 ; j < 2 ; j++)
        {
            buffer[j][i] = folder.Process(buffer[j][i]);
        }
    }
}

void Waveshaper::processLFO(float* buffer[2], size_t size)
{
    for(size_t i = 0 ; i < size ; i++)
    {
        for(uint_fast8_t j = 0 ; j < 2 ; j++)
        {
            buffer[j][i] *= lfo.Process();
        }
    }
} 

void Waveshaper::processBitReducer(float* buffer[2], size_t size)
{
    for(size_t i = 0 ; i < size ; i++)
    {
        for(uint_fast8_t j = 0 ; j < 2 ; j++)
        {
            
        }
    }
}