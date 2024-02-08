#include "Mixer.h"

void Mixer::init(daisy::DaisySeed* seed, float* m[2], float* t1[2], float* t2[2], float* t3[2], float* t4[2], DelayLine<float, MAXDELAY>* dl[2])
{
    bufferSize = SAMPLERATE * DURATION;
    for(uint_fast8_t i = 0 ; i < 2 ; i++)
        mix[i] = m[i];

    for(size_t j = 0 ; j < bufferSize ; j++)
    {
        mix[L][j] = 0.0f;
        mix[R][j] = 0.0f;
    }

    track1.track.init(seed, t1, dl, daisy::seed::D0, daisy::seed::D1);
    track1.gainParam.init(seed, 0, 1, LINEAR, ChannelIDs::Amp1, [this] (float g) { setTrack1Gain(g); });
    for(int i = 0 ; i < 2 ; i++)
        track1.buffer[i] = t1[i];
    
    //track2.track.init(t2);
    //track3.track.init(t3);
    //track4.track.init(t4);
}

void Mixer::tick()
{
    track1.track.tick();
    track1.gainParam.tick();
}

void Mixer::prepare()
{

}

void Mixer::processInputBlock(const float* left, const float* right, size_t size)
{
    track1.track.processInputBlock(left, right, size);
}

void Mixer::processOutputBlock(float* left, float* right, size_t size)
{
    track1.track.processOutputBlock(mix[L], mix[R], size);

    for(size_t i = 0 ; i < size ; i++)
    {
        left[i] = mix[L][i];//track1.gain;
        right[i] = mix[R][i];//track1.gain;
    }
}