#ifndef REVERBVIEW_H
#define REVERBVIEW_H

/*************************************************//**
 *  Class name: ReverbView
 *  Function: FX level GUI class for the reverb
 ****************************************************/

class ReverbView
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