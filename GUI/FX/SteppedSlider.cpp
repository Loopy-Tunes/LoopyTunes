#include "SteppedSlider.h"

void SteppedSlider::init(int ID, EncoderDriver* ed)
{
    driver = ed;
    
    paramID = ID;
    param = driver->getParameter(paramID);

    prevVal = 0;
    isSelected = false;
}

void SteppedSlider::tick()
{
    // fetch curVal from slider pointer
    // if changed
        // repaint
}

void SteppedSlider::paint()
{
    // paint slider
}

void SteppedSlider::repaint()
{
    // update slider if value has changed
}