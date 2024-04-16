#ifndef STEPPEDSLIDER_H
#define STEPPEDSLIDER_H

#include "../../Drivers/EncoderDriver.h"


/********************************************************//**
 *  Class name: SteppedSlider
 *  Function: Slider for representing stepped parameters
 ***********************************************************/

class SteppedSlider
{
public:

    void init(int ID, EncoderDriver* ed);
    void tick();

    void setIsSelected(bool s) { isSelected = s; }

    void paint();
    void repaint();

private:

    EncoderDriver* driver;
    
    int paramID;
    SteppedParameter* param;
    float prevVal;
    bool isSelected;
};

#endif