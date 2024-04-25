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

    void setIsOpen(bool state) { isOpen = state; }
    void setIsPainted(bool state) { isPainted = state; }
    void setCurrentParam(int newParam) { currentParam = newParam; }

private:

    int trackID;

    UiDriver* lcd;
    KeypadDriver* keypad;

    BypassButton bypass;
    SteppedSlider amount;
    SteppedSlider size;
    SteppedSlider feedback; 

    int numberOfParameters = 3;
    const char* parameterNames[3] = {"Amount", "Size", "Feedback"};
    int currentParam = 0;

    bool isOpen;
    bool isPainted;
    int bypassIndexes[4] = {2, 7, 12, 17};
};

#endif