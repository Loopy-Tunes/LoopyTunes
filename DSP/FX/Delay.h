#ifndef DELAY_H
#define DELAY_H

#include "../../Parameters/DefaultValues.h"
#include "../../Drivers/EncoderDriver.h"

#define MAXDELAY 240000 // 5 second max delay

/************************************************************//**
 *  Class name: Delay
 *  Function: Processes delay effect for block of input samples
 ***************************************************************/
using namespace daisysp;

class Delay
{
public:

    /******************************************************************************//**
    * @brief Initialises the instance
    * @param driver A pointer to the encoder driver used to initialise the parameters
    * @param size The size of the block of samples
    * @param trackID The ID of the track the instance belongs to
    * @param dl A pointer to an array of delay lines to be used by the instance
    *********************************************************************************/
    void init(EncoderDriver* driver, int trackID, DelayLine<float, MAXDELAY>* dl[2]);

    /***********************************************************************//**
    * @brief Sets tthe default parameter values
    ***************************************************************************/
    void setDefaultValues();

    /***********************************************************************//**
    * @brief Sets the bypass state of the instance
    ***************************************************************************/
    inline void setBypass() { isBypass = !isBypass; }

    /***********************************************************************//**
    * @brief Sets the amount of the effect in the output
    ***************************************************************************/
    inline void setAmount(float a) { amount.value = a; }

     /***********************************************************************//**
    * @brief Sets the delay time of the delay line 
    * @param s The new delay time
    ***************************************************************************/
    inline void setDelay(size_t s) { delayLine[0]->SetDelay(s), delayLine[1]->SetDelay(s); }

     /***********************************************************************//**
    * @brief Sets the feedback value used in the delay algorithm
    * @param f The new feedback value 
    ***************************************************************************/
    inline void setFeedback(float f) { feedback.value = f; }

    /***************************************************************************//**
    * @brief Processes a block of samples through the delay and mixes the output
    * @param input An array of pointers pointing to the input buffer
    * @param size The size of the block of samples
    *******************************************************************************/
    void processBlock(float* input[2], size_t size); 

private:

    template<typename type>
    type toSize(type toConvert)
    {
        return round((size_t)toConvert);
    }

    bool isBypass;
    SteppedParameterWrapper amount;
    SteppedParameterWrapper size;
    SteppedParameterWrapper feedback;

    DelayLine<float, MAXDELAY>* delayLine[2];
};

#endif