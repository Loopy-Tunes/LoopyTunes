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

    void setIsOpen(bool state) { isOpen = state; }
    void setIsPainted(bool state) { isPainted = state; }

private:

    int trackID;

    UiDriver* lcd;
    KeypadDriver* keypad;

    BypassButton bypass;
    SteppedSlider amount;
    SteppedSlider size;

    bool isOpen;
    bool isPainted;
    int bypassIndexes[4] = {4, 9, 14, 19};
};

#endif