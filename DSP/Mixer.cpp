#include "Mixer.h"

void Mixer::prepare()
{

}

void Mixer::init()
{

}

void Mixer::processBlock(float inputL, float inputR, float outputL, float outputR, size_t size)
{
    /*
    TO DO:
    - Input routing for which track is being recorded into
    - Output mixing
    */

    // if record
        // called in processoor
        // input from processor
        // feed into tracks

    // if playback
        // input from tracks
        // calls get method for tracks
        // mix outputs
        // output to processor

    track1.track.processBlock(inputL, inputR, outputL, outputR, size);
}

