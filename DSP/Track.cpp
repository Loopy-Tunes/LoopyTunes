#include "Track.h"

void Track::init(float* mem[2])
{
    bufferSize = SAMPLERATE * DURATION;
    for(int i = 0 ; i < 2 ; i++)
        buffer[i] = mem[i];

    for(size_t i = 0 ; i < bufferSize ; i++)
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

void Track::tick()
{
    
}

void Track::setIsRecording()
{
    ph.isRecording = !ph.isRecording;

    if(!ph.isRecording)
    {
        ti.isEmpty = false;
        ti.loopLength = ph.writePos;
    }

    ph.reset();
}

void Track::setIsPlaying()
{
    ph.isPlaying = !ph.isPlaying;
    ph.reset();
}

void Track::incrementWritePos()
{
    if(ph.writePos >= (bufferSize - 1))
        ph.writePos = 0;
    else
        ph.writePos++;
}

void Track::incrementReadPos()
{
    if(ph.readPos >= (ti.loopLength - 1))
        ph.readPos = 0;
    else
        ph.readPos++;
}

void Track::prepare()
{

}

void Track::processInputBlock(const float* left, const float* right, size_t size)
{
    if(!ph.isRecording)
        return;

    for(size_t i = 0 ; i < size ; i++)
    {
        buffer[L][ph.writePos] = left[i];
        buffer[R][ph.writePos] = right[i];

        incrementWritePos();
    }
}

std::pair<float*, float*> Track::processOutput()
{
    auto curSample = std::make_pair(&buffer[L][ph.readPos], &buffer[R][ph.readPos]);
    incrementReadPos();

    return curSample;
}