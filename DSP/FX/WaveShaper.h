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

    /*******************************************************************************//**
    * @brief Initialises the instance
    * @param driver A pointer to the encoder driver used to initialise the parameters
    * @param trackID The ID of the track the instance belongs to
    ***********************************************************************************/
    void init(EncoderDriver* driver, int trackID);

    /***********************************************************************//**
    * @brief Sets tthe default parameter values
    ***************************************************************************/
    void setDefaultValues();

    /***********************************************************************//**
    * @brief Sets the bypass state of the instance
    ***************************************************************************/
    void setBypass() { isBypass = !isBypass; }

    /***********************************************************************//**
    * @brief Sets the amount of the effect in the output
    ***************************************************************************/
    inline void setAmount(float a) { amount.value = a; }

    /***********************************************************************//**
    * @brief Sets the function control value of the instance
    ***************************************************************************/
    inline void setFuncControl(float fc);

    /***********************************************************************//**
    * @brief Sets the mode of the instance
    ***************************************************************************/
    inline void setMode(float m) { mode.value = m; }

    /*************************************************************************************//**
    * @brief Scales the value of the function control value for use with the different modes
    *****************************************************************************************/
    inline void scaleControlParam();

    /***********************************************************************//**
    * @brief Sets the input values to be used with the auto gain system
    ***************************************************************************/
    inline void setInputAG(float* buffer[2], size_t size);

    /***********************************************************************//**
    * @brief Sets the output values to be used with the auto gain system
    ***************************************************************************/
    inline void setOutputAG(float* buffer[2], size_t size);

    /***********************************************************************//**
    * @brief Sets the auto gain value for each sample in the block
    * @param size The size of the block of samples
    ***************************************************************************/
    inline void calculateAutoGain(size_t size);

    /***********************************************************************//**
    * @brief Applies the calculated auto gain values to a block of samples
    * @param buffer The buffer the auto gain is to be applied to
    * @param size The size of the buffer in samples
    ***************************************************************************/
    inline void applyAutoGain(float* buffer[2], size_t size);

    /***********************************************************************//**
    * @brief Processes a block of samples
    * @param input The block of samples
    * @param size The size of the block of samples
    ***************************************************************************/
    void processBlock(float* input[2], size_t size);

    /***********************************************************************//**
    * @brief Processes a block of samples using the clipper algorithm
    * @param input The block of samples
    * @param size The size of the block of samples
    ***************************************************************************/
    void processClipper(float* input[2], size_t size);

    /***********************************************************************//**
    * @brief Processes a block of samples using the wavefolder
    * @param input The block of samples
    * @param size The size of the block of samples
    ***************************************************************************/
    void processFolder(float* input[2], size_t size);

    /***********************************************************************//**
    * @brief Modulates each sample in the block using an LFO
    * @param input The block of samples
    * @param size The size of the block of samples
    ***************************************************************************/
    void processLFO(float* input[2], size_t size);

    /***********************************************************************//**
    * @brief Reduces the bit depth of each sample in a block
    * @param input The block of samples
    * @param size The size of the block of samples
    ***************************************************************************/
    void processBitReducer(float* input[2], size_t size);

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

    float buffer[2][BLOCKLENGTH];
    float inputAG[2][BLOCKLENGTH];
    float outputAG[2][BLOCKLENGTH];
    float diffAG[2][BLOCKLENGTH];

    bool isBypass;
    SteppedParameterWrapper amount;
    SteppedParameterWrapper funcControl;
    SteppedParameterWrapper mode;
};

#endif