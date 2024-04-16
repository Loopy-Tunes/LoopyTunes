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

private:

    int trackID;

    UiDriver* lcd;
    KeypadDriver* keypad;

    // bypass
    SteppedSlider amount;
    SteppedSlider funcControl;
    SteppedSlider mode;

    bool isOpen;
};

#endif