#include "Mixer.h"

void Mixer::init(daisy::DaisySeed* seed, float* m[2], float* t1[2], float* t2[2], float* t3[2], float* t4[2])
{
    bufferSize = SAMPLERATE * DURATION;
    for(int i = 0 ; i < 2 ; i++)
        mix[i] = m[i];

    for(size_t j = 0 ; j < bufferSize ; j++)
    {
        mix[L][j] = 0.0f;
        mix[R][j] = 0.0f;
    }

    track1.track.init(t1);
    track2.track.init(t2);
    track3.track.init(t3);
    track4.track.init(t4);

    track1.gain.init(seed, 0, 1, LINEAR, ChannelIDs::Amp1);
}

void Mixer::initParameters()
{

}

void Mixer::prepare()
{

}

void Mixer::tick()
{
    //track1.track.tick();
    track1.gain.tick();
}

void Mixer::processInputBlock(const float* left, const float* right, size_t size)
{
    track1.track.processInputBlock(left, right, size);
}

void Mixer::processOutputBlock(float* left, float* right, size_t size)
{
    // mix samples here
    for(size_t i = 0 ; i < size ; i++)
    {
        if(track1.track.getIsRecording() || track1.track.getIsPlaying())
            track1.curSample = track1.track.processOutput();

        left = track1.curSample.first;
        right = track1.curSample.second;
    }
}