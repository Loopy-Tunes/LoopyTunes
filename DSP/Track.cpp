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

    ti.isEmpty = true;
    ti.loopLength = 0;
}

void Track::prepare()
{

}

void Track::tick()
{
    if(!ph.isPlaying && !ph.isRecording)
        return;

    incrementPlayhead();
}

void Track::setIsRecording()
{
    ph.isRecording = !ph.isRecording;

    if(!ph.isRecording)
    {
        ti.isEmpty = false;
        ti.loopLength = ph.pos;
    }

    ph.reset();
}

void Track::setIsPlaying()
{
    ph.isPlaying = !ph.isPlaying;
    ph.reset();
}

void Track::incrementPlayhead()
{
    if(!ph.isRecording || !ph.isPlaying)
        return;

    if(ph.isRecording)
    {
        if(ph.pos > (bufferSize - 1))
            ph.pos = 0;
        else
            ph.pos++;
    } else if(ph.isPlaying)
    {
        if(ph.pos > (ti.loopLength - 1))
            ph.pos = 0;
        else
            ph.pos++;
    }
}

void Track::processInputBlock(const float* left, const float* right, size_t size)
{
    //if(!ph.isRecording)
        //return;

    for(size_t i = 0 ; i < size ; i++)
    {
        buffer[L][ph.pos] = left[i];
        buffer[R][ph.pos] = right[i];

        tick();
    }
}

 void Track::processOutputBlock(float* left, float* right, size_t size)
 {
    //if(!ph.isPlaying)
        //return;

    for(size_t i = 0 ; i < size ; i++)
    {
        left[i] = buffer[L][ph.pos];
        right[i] = buffer[R][ph.pos];

        tick();
    }
 }