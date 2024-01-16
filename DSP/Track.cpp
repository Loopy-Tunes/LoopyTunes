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
    for(size_t i = 0 ; i < size ; i++)
    {



        ph.pos++;
    }
}