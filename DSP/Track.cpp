#include "Track.h"

void Track::init(float* mem[2])
{
    state = STOPPED;
    ph.reset();
    ti.isEmpty = true;
    ti.loopLength = 0;

    bufferSize = SAMPLERATE * DURATION;
    for(uint_fast8_t i = 0 ; i < 2 ; i++)
        buffer[i] = mem[i];

    for(size_t i = 0 ; i < bufferSize ; i++)
    {
        buffer[L][i] = 0.0f;
        buffer[R][i] = 0.0f;
    }
}

void Track::initIO(TrackIO io)
{
    record.init(io.record, 1000, [this]{ setIsRecording(); });
    play.init(io.play, 1000, [this]{ setIsPlaying(); });
}

void Track::initFX(DaisySeed* seed, DelayLine<float, MAXDELAY>* dl[2])
{
    delay.init(seed, dl);
    shaper.init(seed);
}

void Track::tick()
{
    record.tick();
    play.tick();
    shaper.tick();
    delay.tick();
    reverb.tick();
}

void Track::clearBuffer()
{
    for(size_t i = 0 ; i < bufferSize ; i++)
    {
        buffer[L][i] = 0.0f;
        buffer[R][i] = 0.0f;
    }
}

void Track::setIsRecording()
{
    switch(state)
    {
        case RECORDING:
            state = STOPPED;
            ti.loopLength = ph.writePos;
            break;
        case PLAYING:
            state = RECORDING;
            break;
        case STOPPED:
            state = RECORDING;
            break;
    }

    ph.reset();
}

void Track::setIsPlaying()
{
    switch(state)
    {
        case RECORDING:
            state = PLAYING;
            break;
        case PLAYING:
            state = STOPPED;
            break;
        case STOPPED:
            state = PLAYING;
            break;
    }

    ph.reset();
}

void Track::incrementWritePos()
{
    if(ph.writePos >= bufferSize)
        ph.writePos = 0;
    else
        ph.writePos++;
}

void Track::incrementReadPos()
{
    if(state == RECORDING)
    {
        if(ph.writePos <= 0)
            ph.readPos = 0;
        else
            ph.readPos = ph.writePos - 1;
    } else if(state == PLAYING)
    {
        if(ph.readPos >= ti.loopLength)
            ph.readPos = 0;
        else
            ph.readPos++;
    }
}

void Track::prepare()
{

}

void Track::processInputBlock(const float* left, const float* right, size_t size)
{
    if(state != RECORDING)
        return;

    for(size_t i = 0 ; i < size ; i++)
    {
        buffer[L][ph.writePos] = left[i];
        buffer[R][ph.writePos] = right[i];

        incrementWritePos();
    }
}

void Track::processOutputBlock(float* left, float* right, size_t size)
{
    if(state == STOPPED)
        return;

    // shaper.processBlock(buffer, size, ph.readPos);
    // delay.processBlock(buffer, size, ph.readPos);
    reverb.processBlock(buffer, size);

    for(size_t i = 0 ; i < size ; i++)
    {
        left[i] = buffer[L][ph.readPos];
        right[i] = buffer[R][ph.readPos];
        
        incrementReadPos();
    }
}