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

    void init(int ID, EncoderDriver* driver);
    void tick();

    void repaint();
    void clear();

private:

    // lcd driver pointer
    // keypad driver

    int trackID;

    // bypass
    SteppedSlider amount;
    SteppedSlider size;
    SteppedSlider feedback; 

    bool isOpen;
};

#endif