#include "Track.h"

void Track::init(daisy::DaisySeed* seed, float* mem[2], DelayLine<float, MAXDELAY>* dl[2], dsy_gpio_pin r, dsy_gpio_pin p)
{
    ph.isRecording = false;
    ph.isPlaying = false;
    ph.reset();

    ti.isEmpty = true;
    ti.loopLength = 0;

    record.init(r, 1000, [this]{ setIsRecording(); });
    play.init(p, 1000, [this]{ setIsPlaying(); });

    bufferSize = SAMPLERATE * DURATION;
    for(uint_fast8_t i = 0 ; i < 2 ; i++)
        buffer[i] = mem[i];

    for(size_t i = 0 ; i < bufferSize ; i++)
    {
        buffer[L][i] = 0.0f;
        buffer[R][i] = 0.0f;
    }

    delay.init(seed, dl);
}

void Track::tick()
{
    record.tick();
    play.tick();
    delay.tick();
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
    ph.isRecording = !ph.isRecording;

    if(!ph.isRecording)
    {
        ti.isEmpty = false;
        ti.loopLength = ph.writePos;
    } 

    clearBuffer();
    ph.reset();
}

void Track::setIsPlaying()
{
    ph.isPlaying = !ph.isPlaying;

    if(ph.isPlaying)
    {
        ph.isRecording = false;
    }

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

void Track::processOutputBlock(float* left, float* right, size_t size)
{
    if(!ph.isRecording && !ph.isPlaying)
        return;

    // distortion process block
    // delay.processBlock(buffer, size, ph.readPos);

    for(size_t i = 0 ; i < size ; i++)
    {
        left[i] = buffer[L][ph.readPos];
        right[i] = buffer[R][ph.readPos];
        
        incrementReadPos();
    }
}

