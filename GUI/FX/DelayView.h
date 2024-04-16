#ifndef DELAYVIEW_H
#define DELAYVIEW_H

#include "SteppedSlider.h"

/*************************************************//**
 *  Class name: DelayView
 *  Function: FX level GUI class for the delay
 ****************************************************/

class DelayView
{
public:

    void init(int ID, EncoderDriver* driver, UiDriver* uid, KeypadDriver* kpd);
    void tick();

    void repaint();
    void clear();

private:

    int trackID;

    UiDriver* lcd;
    KeypadDriver* keypad;

    // bypass
    SteppedSlider amount;
    SteppedSlider size;
    SteppedSlider feedback; 

    bool isOpen;
};

#endif