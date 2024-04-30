#include "Mixer.h"

void Mixer::init(DaisySeed* seed, float* t1[2], float* t2[2], float* t3[2], float* t4[2])
{
    bufferSize = SAMPLERATE * DURATION;
    
    track1.track.init(t1, ParameterIDs::Tracks::Track1, seed::D19, seed::D20);
    track2.track.init(t2, ParameterIDs::Tracks::Track2, seed::D21, seed::D22);
    track3.track.init(t3, ParameterIDs::Tracks::Track3, seed::D23, seed::D24);
    track4.track.init(t4, ParameterIDs::Tracks::Track4, seed::D6, seed::D5);

    track1.gain.param.init(seed, 0, 1, LINEAR, ChannelIDs::AMP1, [this] (float g) { setTrack1Gain(g); });
    track2.gain.param.init(seed, 0, 1, LINEAR, ChannelIDs::AMP2, [this] (float g) { setTrack2Gain(g); });
    track3.gain.param.init(seed, 0, 1, LINEAR, ChannelIDs::AMP3, [this] (float g) { setTrack3Gain(g); });
    track4.gain.param.init(seed, 0, 1, LINEAR, ChannelIDs::AMP4, [this] (float g) { setTrack4Gain(g); });

    mixDiv = 0;
    master.param.init(seed, 0, 1, LINEAR, ChannelIDs::MASTER, [this] ( float v) { setMasterVolume(v); }); 
}

void Mixer::initMixChannels(float* m[2], float* t1[2], float* t2[2], float* t3[2], float* t4[2])
{
    for(int i = 0 ; i < 2 ; i++) // assign pointers
    {
        mix[i] = m[i];

        track1.buffer[i] = t1[i];
        track2.buffer[i] = t2[i];
        track3.buffer[i] = t3[i];
        track4.buffer[i] = t4[i];
    }

    for(size_t i = 0 ; i < BLOCKLENGTH ; i++) // initialise
    {
        mix[L][i] = 0.0f;
        mix[R][i] = 0.0f;
        track1.buffer[L][i] = 0.0f;
        track1.buffer[R][i] = 0.0f;
        track2.buffer[L][i] = 0.0f;
        track2.buffer[R][i] = 0.0f;
        track3.buffer[L][i] = 0.0f;
        track3.buffer[R][i] = 0.0f;
        track4.buffer[L][i] = 0.0f;
        track4.buffer[R][i] = 0.0f;
    }
}

void Mixer::initFX(EncoderDriver* driver, DelayLine<float, MAXDELAY>* t1[2], DelayLine<float, MAXDELAY>* t2[2], 
                                          DelayLine<float, MAXDELAY>* t3[2], DelayLine<float, MAXDELAY>* t4[2])
{
    track1.track.initFX(driver, t1);
    track2.track.initFX(driver, t2);
    track3.track.initFX(driver, t3);
    track4.track.initFX(driver, t4);
}

void Mixer::tick()
{
    track1.track.tick();
    track1.gain.param.tick();

    track2.track.tick();
    track2.gain.param.tick();

    track3.track.tick();
    track3.gain.param.tick();

    track4.track.tick();
    track4.gain.param.tick();

    master.param.tick();
}

void Mixer::processInputBlock(const float* left, const float* right, size_t size)
{
    track1.track.processInputBlock(left, right, size);
    track2.track.processInputBlock(left, right, size);
    track3.track.processInputBlock(left, right, size);
    track4.track.processInputBlock(left, right, size);
}

void Mixer::panChannels(size_t size)
{
    panMixBuffer(track1.buffer, track1.pan.value, size);
    panMixBuffer(track2.buffer, track2.pan.value, size);
    panMixBuffer(track3.buffer, track3.pan.value, size);
    panMixBuffer(track4.buffer, track4.pan.value, size);
}

void Mixer::mixOutput(size_t size)
{
    setMixDiv();

    for(size_t i = 0 ; i < size ; i++)
    {
        mix[L][i] = track1.getCurVal(L, i);
        mix[R][i] = track1.getCurVal(R, i);

        /*
        mix[L][i] = (track1.getCurVal(L, i)
                    + track2.getCurVal(L, i)
                    + track3.getCurVal(L, i)
                    + track4.getCurVal(L, i))
                    / mixDiv;
        mix[R][i] = (track1.getCurVal(R, i)
                    + track2.getCurVal(R, i)
                    + track3.getCurVal(R, i)
                    + track4.getCurVal(R, i))
                    / mixDiv;
        */
    }
}

void Mixer::processOutputBlock(float* left, float* right, size_t size)
{
    track1.track.processOutputBlock(track1.buffer, size);
    track2.track.processOutputBlock(track2.buffer, size);
    track3.track.processOutputBlock(track3.buffer, size);
    track4.track.processOutputBlock(track4.buffer, size);

    //panChannels(size);
    mixOutput(size);

    for(size_t i = 0 ; i < size ; i++)
    {
        left[i] = mix[L][i] * master.value;
        right[i] = mix[R][i] * master.value;
    }
}

void Mixer::panMixBuffer(float* buffer[2], float pan, size_t size)
{
    // -6dB linear taper
    for(size_t i = 0 ; i < size ; i++)
    {
        buffer[L][i] = (1 - pan) * buffer[L][i];
        buffer[R][i] = pan * buffer[R][i];
    }
}

void Mixer::setMixDiv()
{
    mixDiv = 0;

    if(track1.track.getState() != STOPPED)
        mixDiv++;
    if(track2.track.getState() != STOPPED)
        mixDiv++;
    if(track3.track.getState() != STOPPED)
        mixDiv++;
    if(track4.track.getState() != STOPPED)
        mixDiv++;
    
    if(mixDiv > 4)
        mixDiv = 4;
}