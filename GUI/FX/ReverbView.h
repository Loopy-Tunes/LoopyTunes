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