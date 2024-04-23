#ifndef FILTERVIEW_H
#define FILTERVIEW_H

#include "SteppedSlider.h"

/*************************************************//**
 *  Class name: FilterView
 *  Function: FX level GUI class for the filter
 ****************************************************/

class FilterView
{
public:

    void init(int ID, EncoderDriver* driver, UiDriver* uid, KeypadDriver* kpd);
    void tick();

    void repaint();
    void clear();

    void setIsOpen(bool state) { isOpen = state; }

private:

    int trackID;

    UiDriver* lcd;
    KeypadDriver* keypad;

    BypassButton bypass;
    SteppedSlider mode;
    SteppedSlider frequency;
    SteppedSlider resonance;

    bool isOpen;
    int bypassIndexes[4] = {2, 7, 12, 17};
};

#endif