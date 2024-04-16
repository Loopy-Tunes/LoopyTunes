#ifndef AUDIOSLIDER_H
#define AUDIOSLIDER_H

#include "daisy_seed.h"

/********************************************************//**
 *  Class name: AudioSlider
 *  Function: Slider for representing audio parameters
 ***********************************************************/

using namespace daisy;

class AudioSlider
{
public:

    void init(int ID, DaisySeed* seed);
    void tick();

    void repaint();

private:

    DaisySeed* hw;
    float input;
    const float jitter = 0.01f;
    
    int channelID;
    bool isMixerView;
};

#endif