#ifndef STEPPEDSLIDER_H
#define STEPPEDSLIDER_H

#include "../../Drivers/KeypadDriver.h"
#include "BypassButton.h"

/********************************************************//**
 *  Class name: SteppedSlider
 *  Function: Slider for representing stepped parameters
 ***********************************************************/

class SteppedSlider
{
public:

    /***********************************************************************//**
    * @brief Initialises the instance
    * @param ID The ID of the parameter the instance is assigned to
    * @param ed A pointer to the encoder driver
    * @param uid A pointer to the LCD driver
    ***************************************************************************/
    void init(int ID, EncoderDriver* ed, UiDriver* uid);
    
    /***************************************************************************//**
    * @brief Handles the updating of the slider to reflect any backend changes
    *******************************************************************************/
    void tick();

    /***********************************************************************//**
    * @brief Changes the selected state to of the slider
    ***************************************************************************/
    void setSelected();

    /***********************************************************************//**
    * @brief Handles the repainting of the slider
    ***************************************************************************/
    void repaint();

private:

    EncoderDriver* encoder;
    UiDriver* lcd;
    
    int paramID;
    SteppedParameter* param;
    float curVal;
};

#endif