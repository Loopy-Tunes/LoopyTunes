#ifndef DELAYVIEW_H
#define DELAYVIEW_H

/*************************************************//**
 *  Class name: DelayView
 *  Function: FX level GUI class for the delay
 ****************************************************/

class DelayView
{
public:

    void init(int ID);
    void tick();

    void paint();

private:

    // lcd driver pointer
    // keypad driver

    // parameter controls

    bool isOpen;
    int effectID;
};

#endif