#include "SteppedSlider.h"

void SteppedSlider::init(int ID, EncoderDriver* ed, UiDriver* uid)
{
    encoder = ed;
    lcd = uid;
    
    paramID = ID;
    param = encoder->getParameter(paramID);

    curVal = 0;
}

void SteppedSlider::tick()
{
    float newVal = param->getCurVal();
    if(newVal != curVal)
    {
        curVal = newVal;
        repaint();
    }
}

void SteppedSlider::setSelected()
{
    encoder->setCurrentParam(paramID);
}

void SteppedSlider::repaint()
{
    // paint slider using curVal
}