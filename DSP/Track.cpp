#include "Track.h"

void Track::prepare()
{

}

void Track::init(float *memL, float *memR, size_t buffSize)
{
    buffer.left = memL;
    buffer.right = memR;
    buffer.size = buffSize;

    buffer.init();
}

void Track::processBlock(StereoBuffer input, StereoBuffer output, size_t size)
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
    buffer.left = input.left;
    buffer.right = input.right;

    output.left = buffer.left;
    output.right = buffer.right;
}