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