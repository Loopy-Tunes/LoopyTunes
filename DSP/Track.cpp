#include "Track.h"

void Track::init(float* mem[2], int ID, dsy_gpio_pin r, dsy_gpio_pin p)
{
    trackID = ID;

    record.init(r, 1000, [this]{ setIsRecording(); });
    play.init(p, 1000, [this]{ setIsPlaying(); });

    state = STOPPED;
    ph.reset();
    ti.isEmpty = true;
    ti.loopLength = 0;

    bufferSize = SAMPLERATE * DURATION;
    buffer[L] = mem[L];
    buffer[R] = mem[R];
    resetBuffer();

    loopStart = 15;
    startPos = 0;
}

void Track::initFX(EncoderDriver* driver, DelayLine<float, MAXDELAY>* dl[2])
{
    pitchShift.init(driver, trackID);
    shaper.init(driver, trackID);
    filter.init(driver, trackID);
    delay.init(driver, trackID, dl);
    reverb.init(driver, trackID);
}

void Track::tick()
{
    record.tick();
    play.tick();
}

void Track::resetBuffer()
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
            setLoopStart();
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

void Track::processOutputBlock(float* output[2], size_t size)
{
    if(state == STOPPED)
        return;

    for(size_t i = 0 ; i < size ; i++)
    {
        output[L][i] = buffer[L][ph.readPos];
        output[R][i] = buffer[R][ph.readPos];

        //output[L][i] = calculateLoop(buffer[L][ph.readPos], L);
        //output[R][i] = calculateLoop(buffer[R][ph.readPos], R);
        
        incrementReadPos();
    }
   
    //pitchShift.processBlock(output, size);
    //shaper.processBlock(output, size); 
    //filter.processBlock(output, size);
    //delay.processBlock(output, size);
    //reverb.processBlock(output, size);
}