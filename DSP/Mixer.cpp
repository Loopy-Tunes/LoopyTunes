#include "Mixer.h"

void Mixer::init(float* m[2], float* t1[2], float* t2[2], float* t3[2], float* t4[2], size_t s)
{
    bufferSize = s;
    buffer[L] = m[L];
    buffer[R] = m[R];

    for(size_t i = 0 ; i < bufferSize ; i++)
    {
        buffer[L][i] = 0.0f;
        buffer[R][i] = 0.0f;
    }

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

