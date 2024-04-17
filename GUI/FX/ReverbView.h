#ifndef REVERBVIEW_H
#define REVERBVIEW_H

#include "SteppedSlider.h"

/*************************************************//**
 *  Class name: ReverbView
 *  Function: FX level GUI class for the reverb
 ****************************************************/

class ReverbView
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

    BypassButton bypass;
    SteppedSlider amount;
    SteppedSlider size;

    bool isOpen;
};

#endif