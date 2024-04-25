#ifndef PITCHSHIFTIEW_H
#define PITCHSHIFTVIEW_H

#include "SteppedSlider.h"

/*************************************************//**
 *  Class name: PitchShiftView
 *  Function: FX level GUI class for the pitch shift
 ****************************************************/

class PitchShiftView
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
    SteppedSlider semitones;

    bool isOpen;
    bool isPainted;
    int bypassIndexes[4] = {0, 5, 10, 15};
};

#endif