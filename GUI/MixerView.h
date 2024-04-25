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

    void init(DaisySeed* seed, EncoderDriver* encoder, UiDriver* uid, KeypadDriver* kpd);
    void tick();

    void repaint();
    void clear();

    void setSelectedChannel(int channel) { selectedChannel = channel; }
    void setIsOpen(bool state) { isOpen = state; }
    void setIsPainted(bool state) { isPainted = state; }

private:

    UiDriver* lcd;
    KeypadDriver* keypad;

    AudioSlider amp1;
    AudioSlider amp2;
    AudioSlider amp3;
    AudioSlider amp4;

    int selectedChannel;
    std::array<AudioSlider, 4> ampSliders = {amp1, amp2, amp3, amp4};

    TrackView track1;
    TrackView track2;
    TrackView track3;
    TrackView track4;

    bool isOpen;
    bool isPainted;
};

#endif