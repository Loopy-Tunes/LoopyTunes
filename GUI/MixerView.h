#ifndef MIXERVIEW_H
#define MIXERVIEW_H

#include "TrackView.h"

/********************************************//**
 *  Class name: MixerView
 *  Function: Top level GUI class 
 ***********************************************/

class MixerView
{
public:

    void init();
    void tick();

    void paint();

    void updateAmplitudes();

private:

    TrackView track1;
    TrackView track2;
    TrackView track3;
    TrackView track4;

    bool isOpen;
};

#endif