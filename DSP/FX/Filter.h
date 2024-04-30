#ifndef FILTER_H
#define FILTER_H

#include "../../Parameters/DefaultValues.h"
#include "../../Drivers/EncoderDriver.h"
#include "../../Utils/Constants.h"

/**********************************************************************************************//**
 *  Class name: Filter
 *  Function: Wrapper for DaisySP ladder filter class that applies a filter to a block of samples
 *************************************************************************************************/
using namespace daisysp;

class Filter
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
    * @brief Sets the cutoff frequency of the filter
    * @param f The new cutoff frequency
    ***************************************************************************/
    void setFreq(float f) { filter.SetFrequency(f); }

    /***********************************************************************//**
    * @brief Sets the mode of the filter, either high pass or low pass
    * @param m the new mode
    ***************************************************************************/
    void setMode(float m);

    /***********************************************************************//**
    * @brief Processes a block of samples through the filter
    * @param input An array of pointers pointing to the input buffer
    * @param size The size of the block of samples
    ***************************************************************************/
    void processBlock(float* input[2], size_t size);

private:

    OnePole filter;

    bool isBypass;
    SteppedParameter mode;
    SteppedParameter freq;
};

#endif