#ifndef PITCHSHIFTER_H
#define PITCHSHIFTER_H

#include "../../Parameters/DefaultValues.h"
#include "../../Drivers/EncoderDriver.h"
#include "../../Utils/Constants.h"

/***************************************************************************************//**
 *  Class name: PitchShift
 *  Function: Wrapper for DaisySP pitch shifter class that pitch shifts a block of samples
 ******************************************************************************************/
using namespace daisysp;

class PitchShift
{
public:

    /******************************************************************************//**
    * @brief Initialises the instance
    * @param driver A pointer to the encoder driver used to initialise the parameters
    * @param size The size of the block of samples
    * @param trackID The ID of the track the instance belongs to
    *********************************************************************************/
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
    void setAmount(float a) { amount.value = a; }

    /***********************************************************************//**
    * @brief Pitch shifts a block of samples and mixes it with the input
    * @param input An array of pointers pointing to the input buffer
    * @param size The size of the block of samples
    ***************************************************************************/
    void processBlock(float* input[2], size_t size);

private:

    float buffer[2][BLOCKLENGTH];
    daisysp::PitchShifter shifter;

    bool isBypass;
    SteppedParameterWrapper amount;
    SteppedParameterWrapper semitones;
};

#endif