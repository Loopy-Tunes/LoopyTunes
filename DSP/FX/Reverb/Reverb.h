#ifndef REVERB_H
#define REVERB_H

#include "../../../Parameters/DefaultValues.h"
#include "../../../Drivers/EncoderDriver.h"
#include "../../../Utils/Constants.h"
#include "revmodel.hpp"

/*********************************************************************//**
 *  Class name: Reverb
 *  Function: Processes reverb effect for block of input samples
 * 
 *  Port of the open-source Freeverb algorithm by Jezar (Dreampoint, 2000)
 *  https://github.com/sinshu/freeverb
 ************************************************************************/
using namespace daisysp;

class Reverb
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
    void setAmount(float mix);

    /***************************************************************************//**
    * @brief Processes a block of samples through the reverb and mixes the output
    * @param input An array of pointers pointing to the input buffer
    * @param size The size of the block of samples
    *******************************************************************************/
    void processBlock(float* input[2], long size);

private:

    float output[2][BLOCKLENGTH];
    revmodel model;

    bool isBypass;
    SteppedParameterWrapper amount;
    SteppedParameterWrapper mode;
    SteppedParameterWrapper size;
    SteppedParameterWrapper damp;
    SteppedParameterWrapper width;
};

#endif