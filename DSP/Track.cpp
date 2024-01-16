#include "Track.h"

void Track::prepare()
{

}

void Track::init(float *memL, float *memR, size_t buffSize)
{
    /*
    - fill buffer with 0s
    */
}

void Track::processBlock(float inputL, float inputR, float outputL, float outputR, size_t size)
{
    // processes a block of samples
    // if recording
        // responsible for taking an input and storing it in the track's buffer
    // if playing
        // responsible for processing size samples through fx and sending to mixer

    // if recording
        // copy input to buffer

    // if playing
     // process distortion
     // process delay
    
}