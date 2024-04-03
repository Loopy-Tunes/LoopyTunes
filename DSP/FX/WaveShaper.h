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
 *  Uses fast tanh by John ffitch for the clipper algortihm
 *  Bit reduction algortihm based off Decimator from musicdsp
 *  https://www.musicdsp.org/en/latest/Effects/124-decimator.html 
 **********************************************************************/
using namespace daisysp;

class Waveshaper
{
public:

    void init(EncoderDriver* driver, int trackID);
    void setDefaultValues();
    void tick();

    inline void setBypass(float b) { bypass.value = b; }
    inline void setAmount(float a) { amount.value = a; }
    inline void setFuncControl(float fc) { funcControl.value = fc; }
    inline void setWaveshape(float ws) { waveshape.value = ws; }
    
    inline void scaleControlParam();

    inline void setInputAG(float* buffer[2], size_t size);
    inline void setOutputAG(float* buffer[2], size_t size);
    inline void calculateAutoGain(size_t size);
    inline void applyAutoGain(float* buffer[2], size_t size);

    void processBlock(float* buffer[2], size_t size);
    void processClipper(float* buffer[2], size_t size);
    void processFolder(float* buffer[2], size_t size);
    void processLFO(float* buffer[2], size_t size);
    void processBitReducer(float* buffer[2], size_t size);

private:

    enum Funcs
    {
        CLIPPER = 0,
        FOLDER,
        LFO,
        BITREDUCER
    };

    Wavefolder folder;
    Oscillator lfo;

    float lfoMin, lfoMax;
    float lfoFreq;
    int bitsMin, bitsMax;
    float bitRate, bitCount;
    int bits;

    float inputAG[2][BLOCKLENGTH];
    float outputAG[2][BLOCKLENGTH];
    float diffAG[2][BLOCKLENGTH];

    SteppedParameterWrapper bypass;
    SteppedParameterWrapper amount;
    SteppedParameterWrapper funcControl;
    SteppedParameterWrapper waveshape;
};

#endif