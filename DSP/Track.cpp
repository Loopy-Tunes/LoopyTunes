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

    ph.isRecording = false;
    ph.isPlaying = false;
    ph.reset();
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

void Track::processInput(const float* left, const float* right, size_t size)
{
    for(size_t i = 0 ; i < size ; i++)
    {
        buffer[L][i] = left[i];
        buffer[R][i] = right[i];
    }
}

float* Track::processOutputLeft(size_t pos)
{
    return &buffer[L][pos];
}

float* Track::processOutputRight(size_t pos)
{
    return &buffer[R][pos];
}

void Track::setIsRecording()
{
    ph.isRecording = !ph.isRecording;
    ph.reset();
}

void Track::setIsPlaying()
{
    ph.isPlaying = !ph.isPlaying;
    ph.reset();
}

void Track::incrementPlayhead()
{
    if(!ph.isPlaying)
        return;

    if(ph.pos > (ti.loopLength-1))
        ph.pos = 0;
    else
        ph.pos++;
}