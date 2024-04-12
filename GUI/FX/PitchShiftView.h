#ifndef PITCHSHIFTIEW_H
#define PITCHSHIFTVIEW_H

/*************************************************//**
 *  Class name: PitchShiftView
 *  Function: FX level GUI class for the pitch shift
 ****************************************************/

class PitchShiftView
{
public:

    void init(int ID);
    void tick();

    void paint();
    void clear();

    void updateParameters();

private:

    // lcd driver pointer
    // keypad driver

    // parameter controls

    bool isOpen;
    int effectID;
};

#endif