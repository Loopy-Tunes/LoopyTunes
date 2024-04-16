#include "AudioSlider.h"

void AudioSlider::init(int ID, DaisySeed* seed)
{
    hw = seed;
    input = 0;

    channelID = ID;
    isMixerView = false;
}

void AudioSlider::tick()
{
    if(!isMixerView)
        return;

    float newInput = hw->adc.GetFloat(channelID);
    if(newInput > (input + jitter) || newInput < (input - jitter))
    {
        input = newInput;
        repaint();
    }
}

void AudioSlider::repaint()
{
    
}