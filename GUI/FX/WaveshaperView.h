#ifndef WAVESHAPERVIEW_H
#define WAVESHAPERVIEW_H

/*************************************************//**
 *  Class name: WaveshaperView
 *  Function: FX level GUI class for the Waveshaper
 ****************************************************/

class WaveshaperView
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