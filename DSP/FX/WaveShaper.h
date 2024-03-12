#ifndef WAVESHAPER_H
#define WAVESHAPER_H

#include "../../Parameters/AudioParameter.h"
#include "../../Parameters/BinaryParameter.h"
#include "../../Parameters/DefaultValues.h"
#include <cmath>

/*******************************************************************//**
 *  Class name: Waveshaper
 *  Function: Processes the input samples through a transfer function
 * 
 *  Based off of Adhesion VST (Andrew Ford 2012)
 *  https://github.com/Adhesion/adosin/tree/master
 **********************************************************************/
using namespace daisysp;

class Waveshaper
{
public:

    void init(DaisySeed* seed);
    void setDefaultValues();
    void tick();

    inline void setBypass() { bypass.value = !bypass.value; }
    inline void setAmount(float a) { amount.value = a; }
    inline void setInput(float i) { input.value = i; }
    inline void setWaveshape(int ws) { waveshape.value = ws; }
    
    void calculateAutoGain();
    void processBlock(float* buffer[2], size_t size);

    void processSine(float* buffer[2], size_t size);
    void processTanh(float* buffer[2], size_t size);
    void processSignum(float* buffer[2], size_t size);
    // wave shape 4 process 
    // wave shape 5 process 

private:

    BinaryParameterWrapper bypass;
    AudioParameterWrapper<float> amount;
    AudioParameterWrapper<float> input;
    AudioParameterWrapper<int> waveshape;

    float gain;
};

#endif