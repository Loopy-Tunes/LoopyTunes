#include "Track.h"

void Track::init(float* mem[2], const size_t s)
{
    bufferSize = s;
    for(int i = 0 ; i < 2 ; i++)
        buffer[i] = mem[i];

    for(size_t i = 0 ; i < s ; i++)
    {
        buffer[L][i] = 0.0f;
        buffer[R][i] = 0.0f;
    }
}

void Track::prepare()
{

}

void Track::processBlock(size_t size)
{
    for(size_t i = 0 ; i < size ; i++)
    {
        


        incrementPlayhead();
    }
}

void Track::incrementPlayhead()
{
    // add ph logic here
}