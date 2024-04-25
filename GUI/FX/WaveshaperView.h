#ifndef WAVESHAPERVIEW_H
#define WAVESHAPERVIEW_H

#include "SteppedSlider.h"

/*************************************************//**
 *  Class name: WaveshaperView
 *  Function: FX level GUI class for the Waveshaper
 ****************************************************/

class WaveshaperView
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
    SteppedSlider funcControl;
    SteppedSlider mode;

    int numberOfParameters = 3;
    const char* parameterNames[3] = {"Amount", "Function Control", "Mode"};
    int currentParam = 0;

    bool isOpen;
    bool isPainted;
    int bypassIndexes[4] = {1, 6, 11, 16};
};

#endif