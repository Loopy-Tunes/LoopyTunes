#ifndef WAVESHAPER_H
#define WAVESHAPER_H

#include "../../Parameters/AudioParameter.h"

/************************************************************//**
 *  Class name: Delay
 *  Function: Processes delay effect for block of input sanples
 ***************************************************************/
using namespace daisysp;

class WaveShaper
{
public:

    void init(DaisySeed* seed);
    void tick();

    inline void setBypass(int b) { bypass.value = b; }
    inline void setInput(float i) { input.value = i; }
    inline void setWaveshape(int ws) { waveshape.value = ws; }
    
    void prepare();
    void calculateAutoGain();
    void processBlock(float* input[2], size_t size, size_t readPos);

    // wave shape 1 process 
    // wave shape 2 process 
    // wave shape 3 process 
    // wave shape 4 process 
    // wave shape 5 process 

private:

    ParameterWrapper<int> bypass;
    ParameterWrapper<float> input;
    ParameterWrapper<int> waveshape;

    float gain;
};

#endif