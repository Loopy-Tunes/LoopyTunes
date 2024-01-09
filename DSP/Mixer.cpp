#include "Mixer.h"

void Mixer::prepare()
{

}

void Mixer::processBlock(float* input, size_t size)
{
    // if record
        // called in processoor
        // input from processor
        // feed into tracks

    // if playback
        // input from tracks
        // calls get method for tracks
        // mix outputs
        // output to processor
}

