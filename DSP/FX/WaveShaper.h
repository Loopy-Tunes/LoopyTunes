#ifndef WAVESHAPER_H
#define WAVESHAPER_H

#include "../../Parameters/AudioParameter.h"
#include <cmath>

/************************************************************//**
 *  Class name: Delay
 *  Function: Processes delay effect for block of input sanples
 ***************************************************************/
using namespace daisysp;

class Waveshaper
{
public:

    void init(DaisySeed* seed);
    void tick();

    inline void setBypass(int b) { bypass.value = b; }
    inline void setInput(float i) { input.value = i; }
    inline void setWaveshape(int ws) { waveshape.value = ws; }
    inline void setAmount(float a) { amount.value = a; }
    
    void prepare();
    void calculateAutoGain();
    void processBlock(float* input[2], size_t size, size_t readPos);

    void processSine(float* input[2], size_t size, size_t readPos);
    void processTanh(float* input[2], size_t size, size_t readPos);
    void processSignum(float* input[2], size_t size, size_t readPos);
    // wave shape 4 process 
    // wave shape 5 process 

private:

    ParameterWrapper<int> bypass;
    ParameterWrapper<float> input;
    ParameterWrapper<int> waveshape;
    ParameterWrapper<float> amount;

    float gain;
};

#endif