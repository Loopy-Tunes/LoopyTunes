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

    void init(int ID, EncoderDriver* driver);
    void tick();

    void repaint();
    void clear();

private:

    // lcd driver pointer
    // keypad driver

    // parameter controls

    bool isOpen;
    int effectID;
};

#endif