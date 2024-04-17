#ifndef STEPPEDSLIDER_H
#define STEPPEDSLIDER_H

#include "../../Drivers/EncoderDriver.h"
#include "../../Drivers/daisy_ILI9341.h"
#include "../../Drivers/KeypadDriver.h"
#include "BypassButton.h"

/********************************************************//**
 *  Class name: SteppedSlider
 *  Function: Slider for representing stepped parameters
 ***********************************************************/

class SteppedSlider
{
public:

    void init(int ID, EncoderDriver* ed, UiDriver* uid);
    void tick();

    void setSelected();
    void repaint();

private:

    EncoderDriver* encoder;
    UiDriver* lcd;
    
    int paramID;
    SteppedParameter* param;
    float curVal;
};

#endif