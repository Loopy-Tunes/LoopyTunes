#include "Waveshaper.h"

using namespace daisysp;

void Waveshaper::init(EncoderDriver* driver, int trackID)
{
    for(size_t i = 0 ; i < BLOCKLENGTH ; i++)
    {
        for(u_int8_t j = 0 ; j < 2 ; j++)
        {
            inputAG[j][i] = 0;
            outputAG[j][i] = 0; 
            diffAG[j][i] = 0;  
        }
    }

    folder.Init();
    lfo.Init(48000);
    lfo.SetWaveform(0);
    lfo.SetAmp(0.5);
    lfo.Reset(0);

    lfoMin = 20;
    lfoMax = 128;
    lfoFreq = 0;

    bitsMin = 4;
    bitsMax = 16;
    bitRate = 0.5;
    bitCount = 0;
    bits = 0;

    amount.param.init(0, 1, 0.05, ParameterIDs::Waveshaper::amount, trackID, [this] (float a) { setAmount(a); });
    funcControl.param.init(0, 1, 0.05, ParameterIDs::Waveshaper::funcControl, trackID, [this] (float fc) { setFuncControl(fc); });
    mode.param.init(0, 4, 1, ParameterIDs::Waveshaper::waveshape, trackID, [this] (float m) { setMode(m); });

    driver->addParameter(&amount.param);
    driver->addParameter(&funcControl.param);
    driver->addParameter(&mode.param);

    setDefaultValues();
}

 void Waveshaper::setDefaultValues()
 {
    setBypass(waveshaperDefs.bypass);
    setAmount(waveshaperDefs.amount);
    setFuncControl(funcControl.value = waveshaperDefs.funcControl);
    setMode(waveshaperDefs.mode);
 }

inline void Waveshaper::scaleControlParam()
{
    int modeCheck = mode.value;

    switch(modeCheck)
    {
        case LFO:
            lfoFreq = (funcControl.value - 1) * (lfoMax - lfoMin) / (1 - 0) + lfoMin;
            lfo.SetFreq(lfoFreq);
        break;
        case BITREDUCER:
            bits = (funcControl.value - 1) * (bitsMax - bitsMin) / (1 - 0) + bitsMin;
        break;
    }
}

inline void Waveshaper::setInputAG(float* buffer[2], size_t size) 
{  
    for(size_t i = 0 ; i < size ; i++)
    {
        for(u_int8_t j = 0 ; j < 2 ; j++)
        {
            inputAG[j][i] = buffer[j][i]; 
        }
    }
}

inline void Waveshaper::setOutputAG(float* buffer[2], size_t size) 
{ 
    for(size_t i = 0 ; i < size ; i++)
    {
        for(u_int8_t j = 0 ; j < 2 ; j++)
        {
            outputAG[j][i] = buffer[j][i]; 
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
    if(isBypass)
        return;

    setInputAG(buffer, size);

    int modeCheck = mode.value;
    if(modeCheck == CLIPPER || modeCheck == FOLDER)
    {
        for(size_t i = 0 ; i < BLOCKLENGTH ; i++)
        {
            for(uint_fast8_t j = 0 ; j < 2 ; j++)
            {
                buffer[j][i] *= funcControl.value;
            }
        }
    }

    switch(modeCheck)
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

    if(modeCheck == CLIPPER || modeCheck == FOLDER)
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
            int sign = 1;
            if(buffer[j][i] < 0)
            {
                sign = -1;
                buffer[j][i] = -buffer[j][i];
                buffer[j][i] *= sign;
            }
            else if(buffer[j][i] >= 4.0f)
            {
                buffer[j][i] = sign;
            }
            else if(buffer[j][i] < 0.5f)
            {
                buffer[j][i] *= sign;
            }
            buffer[j][i] = sign * tanhf(buffer[j][i]);
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
    long int m = 1 << (bits-1);

    for(size_t i = 0 ; i < size ; i++)
    {
        bitCount += bitRate;
        for(uint_fast8_t j = 0 ; j < 2 ; j++)
        {
            if(bitCount >= 1)
            {
                buffer[j][i] = (long int)(buffer[j][i] * m) / (float)m;
                if(j == 2)
                    bitCount = 0;
            }
        }
    }
}