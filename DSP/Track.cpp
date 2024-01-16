#include "Track.h"

void Track::init(float* mem, const size_t s)
{
    buffer = mem;
    bufferSize = s;

    for(size_t i = 0 ; i < s ; i++)
        buffer[i] = 0.0f;
}

void Track::prepare()
{

}

void Track::processBlock(size_t size)
{
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