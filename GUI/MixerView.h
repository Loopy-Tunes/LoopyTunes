#ifndef MIXERVIEW_H
#define MIXERVIEW_H

#include "AudioSlider.h"
#include "TrackView.h"

/********************************************//**
 *  Class name: MixerView
 *  Function: Top level GUI class 
 ***********************************************/

class MixerView
{
public:

    void init(DaisySeed* seed, EncoderDriver* driver);
    void tick();

    void repaint();
    void clear();

private:

    AudioSlider amp1;
    AudioSlider amp2;
    AudioSlider amp3;
    AudioSlider amp4;

    TrackView track1;
    TrackView track2;
    TrackView track3;
    TrackView track4;

    bool isOpen;
};

#endif