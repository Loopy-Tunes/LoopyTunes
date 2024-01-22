#include "Mixer.h"

void Mixer::init(float* m[2], float* t1[2], float* t2[2], float* t3[2], float* t4[2], size_t s)
{
    bufferSize = s;
    buffer[L] = m[L];
    buffer[R] = m[R];
    for(int i = 0 ; i < 2 ; i++)
        curSample[i] = nullptr;

    for(size_t j = 0 ; j < bufferSize ; j++)
    {
        buffer[L][j] = 0.0f;
        buffer[R][j] = 0.0f;
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

void Mixer::tick()
{
    track1.track.tick();
}

void Mixer::processInput(const float* left, const float* right, size_t size)
{
    track1.track.processInput(left, right, size);
}

float Mixer::processOutputLeft()
{
    curSample[L] = track1.track.processOutputLeft();

    if(curSample[L] != nullptr)
        return *curSample[L];
    else
        return 0.0f;
}

float Mixer::processOutputRight()
{
    curSample[R] = track1.track.processOutputRight();

    if(curSample[R] != nullptr)
        return *curSample[R];
    else
        return 0.0f;
}