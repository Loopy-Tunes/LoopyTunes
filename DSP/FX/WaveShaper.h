#ifndef WAVESHAPER_H
#define WAVESHAPER_H

#include "../../Parameters/DefaultValues.h"
#include "../../Drivers/EncoderDriver.h"
#include "../../Utils/Constants.h"
#include <cmath>

/*******************************************************************//**
 *  Class name: Waveshaper
 *  Function: Processes the input samples through a transfer function
 * 
 *  Inspired by Adhesion VST (Andrew Ford 2012)
 *  https://github.com/Adhesion/adosin/tree/master
 **********************************************************************/
using namespace daisysp;

class Waveshaper
{
public:

    void init(EncoderDriver* driver, std::string trackID);
    void setDefaultValues();
    void tick();

    inline void setBypass(float b) { bypass.value = b; }
    inline void setAmount(float a) { amount.value = a; }
    inline void setInputGain(float i) { inputGain.value = i; }
    inline void setWaveshape(float ws) { waveshape.value = ws; }
    
    inline void setInputAG(float* buffer[2], size_t size);
    inline void setOutputAG(float* buffer[2], size_t size);
    inline void calculateAutoGain(size_t size);
    inline void applyAutoGain(float* buffer[2], size_t size);

    void processBlock(float* buffer[2], size_t size);
    void processSine(float* buffer[2], size_t size);
    void processTanh(float* buffer[2], size_t size);
    void processSignum(float* buffer[2], size_t size);
    // wave shape 4 process 
    // wave shape 5 process 

private:

    enum Funcs
    {
        SINE = 0,
        TANH,
        SIGNUM
    };

    float inputAG[2][BLOCKLENGTH];
    float outputAG[2][BLOCKLENGTH];
    float diffAG[2][BLOCKLENGTH];

    SteppedParameterWrapper bypass;
    SteppedParameterWrapper amount;
    SteppedParameterWrapper inputGain;
    SteppedParameterWrapper waveshape;
};

#endif