#include "Mixer.h"

void Mixer::init(float* m, float* t1, float* t2, float* t3, float* t4, size_t s)
{
    track1.track.init(t1, s);
    track2.track.init(t2, s);
    track3.track.init(t3, s);
    track4.track.init(t4, s);
}

void Mixer::prepare()
{

}

void Mixer::processBlock(size_t size)
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
}

