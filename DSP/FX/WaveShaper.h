#ifndef WAVESHAPER_H
#define WAVESHAPER_H

#include "../../Parameters/AudioParameter.h"
#include "../../Parameters/BinaryParameter.h"
#include <cmath>

/*******************************************************************//**
 *  Class name: Waveshaper
 *  Function: Processes the input samples through a transfer function
 * 
 *  Based of Adhesion VST (Andrew Ford 2012)
 *  https://github.com/Adhesion/adosin/tree/master
 **********************************************************************/
using namespace daisysp;

class Waveshaper
{
public:

    void init(DaisySeed* seed);
    void tick();

    inline void setBypass() { bypass.value = !bypass.value; }
    inline void setInput(float i) { input.value = i; }
    inline void setWaveshape(int ws) { waveshape.value = ws; }
    inline void setAmount(float a) { amount.value = a; }
    
    void prepare();
    void calculateAutoGain();
    void processBlock(float* buffer[2]);

    void processSine(float* buffer[2]);
    void processTanh(float* buffer[2]);
    void processSignum(float* buffer[2]);
    // wave shape 4 process 
    // wave shape 5 process 

private:

    BinaryParameterWrapper bypass;
    AudioParameterWrapper<float> input;
    AudioParameterWrapper<int> waveshape;
    AudioParameterWrapper<float> amount;

    float gain;
};

#endif