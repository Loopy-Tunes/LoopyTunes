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

private:

    int trackID;

    UiDriver* lcd;
    KeypadDriver* keypad;

    // bypass
    SteppedSlider amount;
    SteppedSlider semitones;

    bool isOpen;
};

#endif