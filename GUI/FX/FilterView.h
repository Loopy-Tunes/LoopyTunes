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
    void setIsPainted(bool state) { isPainted = state; }
    void setCurrentParam(int newParam) { currentParam = newParam; }

private:

    int trackID;

    UiDriver* lcd;
    KeypadDriver* keypad;

    BypassButton bypass;
    SteppedSlider mode;
    SteppedSlider frequency;
    SteppedSlider resonance;

    int numberOfParameters = 3;
    const char* parameterNames[3] = {"Mode", "Frequency", "Resonance"};
    int currentParam = 0;

    bool isOpen;
    bool isPainted;
    int bypassIndexes[4] = {2, 7, 12, 17};
};

#endif