#ifndef AUDIOSLIDER_H
#define AUDIOSLIDER_H

#include "daisy_seed.h"
#include "FX/StyleSheet.h"
#include <string>

/********************************************************//**
 *  Class name: AudioSlider
 *  Function: Slider for representing audio parameters
 ***********************************************************/

using namespace daisy;

class AudioSlider
{
public:

    void init(int ID, DaisySeed* seed, UiDriver* uid);
    void tick();

    void repaint(int index, bool selected);

private:

    DaisySeed* hw;
    UiDriver* lcd;

    float input;
    const float jitter = 0.01f;
    
    int channelID;
    bool isUpdated;
};

#endif