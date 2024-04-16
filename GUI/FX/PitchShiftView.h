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
    SteppedSlider semitones;

    bool isOpen;
};

#endif