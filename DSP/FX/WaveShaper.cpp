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
    lfo.SetAmp(0.75);
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
    funcControl.param.init(0, 1, 0.02, ParameterIDs::Waveshaper::funcControl, trackID, [this] (float fc) { setFuncControl(fc); });
    mode.param.init(0, 4, 1, ParameterIDs::Waveshaper::mode, trackID, [this] (float m) { setMode(m); });

    driver->addBypassCallback([this] { setBypass(); });
    driver->addParameter(&amount.param);
    driver->addParameter(&funcControl.param);
    driver->addParameter(&mode.param);

    setDefaultValues();
}

 void Waveshaper::setDefaultValues()
 {
    isBypass = true;
    setAmount(waveshaperDefs.amount);
    setFuncControl(waveshaperDefs.funcControl);
    setMode(waveshaperDefs.mode);
 }

inline void Waveshaper::setFuncControl(float fc)
{
    funcControl.value = fc;
    scaleControlParam();
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

void Waveshaper::processBlock(float* input[2], size_t size)
{
    if(isBypass)
        return;

    setInputAG(input, size);

    for(size_t i = 0 ; i < BLOCKLENGTH ; i++)
    {
        for(uint_fast8_t j = 0 ; j < 2 ; j++)
        {
            buffer[L][i] = input[L][i];
            buffer[L][i] = input[R][i];
        }
    }

    int modeCheck = mode.value;
    if(mode.value == CLIPPER || mode.value == FOLDER)
    {
        for(size_t i = 0 ; i < BLOCKLENGTH ; i++)
        {
            for(uint_fast8_t j = 0 ; j < 2 ; j++)
            {
                input[j][i] *= funcControl.value;
            }
        }
    }

    switch(modeCheck)
    {
        case CLIPPER:
            processClipper(input, size);
        break;
        case FOLDER:
            processFolder(input, size);
        break;
        case LFO:
            processLFO(input, size);
        break;
        case BITREDUCER:
            processBitReducer(input, size);
        break;
    }

    if(modeCheck == CLIPPER || modeCheck == FOLDER)
    {
        setOutputAG(input, size);
        calculateAutoGain(size);
        applyAutoGain(input, size);
    }

    for(size_t i = 0 ; i < BLOCKLENGTH ; i++)
    {
        for(uint_fast8_t j = 0 ; j < 2 ; j++)
        {
            input[L][i] = (input[L][i] * (1.f - amount.value)) + (buffer[L][i] * amount.value);
            input[R][i] = (input[R][i] * (1.f - amount.value)) + (buffer[R][i] * amount.value);
        }
    }
}

void Waveshaper::processClipper(float* input[2], size_t size)
{
    for(size_t i = 0 ; i < size ; i++)
    {
        for(uint_fast8_t j = 0 ; j < 2 ; j++)
        {
            int sign = 1;
            if(input[j][i] < 0)
            {
                sign = -1;
                input[j][i] = -input[j][i];
                input[j][i] *= sign;
            }
            else if(input[j][i] >= 4.0f)
            {
                input[j][i] = sign;
            }
            else if(input[j][i] < 0.5f)
            {
                input[j][i] *= sign;
            }
            input[j][i] = sign * tanhf(input[j][i]);
        }
    }
} 

void Waveshaper::processFolder(float* input[2], size_t size)
{
    for(size_t i = 0 ; i < size ; i++)
    {
        for(uint_fast8_t j = 0 ; j < 2 ; j++)
        {
            input[j][i] = folder.Process(input[j][i]);
        }
    }
}

void Waveshaper::processLFO(float* input[2], size_t size)
{
    float lfoVal = lfo.Process();

    for(size_t i = 0 ; i < size ; i++)
    {
        for(uint_fast8_t j = 0 ; j < 2 ; j++)
        {
            input[j][i] *= lfoVal;
        }
    }
} 

void Waveshaper::processBitReducer(float* input[2], size_t size)
{
    long int m = 1 << (bits-1);

    for(size_t i = 0 ; i < size ; i++)
    {
        bitCount += bitRate;
        for(uint_fast8_t j = 0 ; j < 2 ; j++)
        {
            if(bitCount >= 1)
            {
                input[j][i] = (long int)(input[j][i] * m) / (float)m;
                if(j == 2)
                    bitCount = 0;
            }
        }
    }
}