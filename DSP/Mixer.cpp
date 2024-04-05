#include "Mixer.h"

void Mixer::init(DaisySeed* seed, float* m[2], float* t1[2], float* t2[2], float* t3[2], float* t4[2])
{
    bufferSize = SAMPLERATE * DURATION;
    for(uint_fast8_t i = 0 ; i < 2 ; i++)
        mix[i] = m[i];

    for(size_t j = 0 ; j < bufferSize ; j++)
    {
        mix[L][j] = 0.0f;
        mix[R][j] = 0.0f;
    }

    track1.track.init(t1);
    // init fx
    track2.track.init(t2);
    // init fx
    track3.track.init(t3);
    // init fx
    track4.track.init(t4);
    // init fx

    mixDiv = 0;
    master.param.init(seed, 0, 1, LINEAR, ChannelIDs::MASTER, [this] ( float v) { setMasterVolume(v); }); 

    limiter.Init();
}

void Mixer::initMixChannels(float* t1[2], float* t2[2], float* t3[2], float* t4[2])
{
    for(int i = 0 ; i < 2 ; i++)
    {
        track1.buffer[i] = t1[i];
        track2.buffer[i] = t2[i];
        track3.buffer[i] = t3[i];
        track4.buffer[i] = t4[i];
    }
}

void Mixer::initTrackIO(DaisySeed* seed, TrackIO t1, TrackIO t2, TrackIO t3, TrackIO t4)
{
    track1.gain.param.init(seed, 0, 1, LINEAR, ChannelIDs::AMP1, [this] (float g) { setTrack1Gain(g); });
    track2.gain.param.init(seed, 0, 1, LINEAR, ChannelIDs::AMP2, [this] (float g) { setTrack2Gain(g); });
    track3.gain.param.init(seed, 0, 1, LINEAR, ChannelIDs::AMP3, [this] (float g) { setTrack3Gain(g); });
    track4.gain.param.init(seed, 0, 1, LINEAR, ChannelIDs::AMP4, [this] (float g) { setTrack4Gain(g); });

    track1.pan.param.init(seed, 0, 1, LINEAR, ChannelIDs::ENCODER, [this] (float p) { setTrack1Pan(p); });
    track2.pan.param.init(seed, 0, 1, LINEAR, ChannelIDs::ENCODER, [this] (float p) { setTrack2Pan(p); });
    track3.pan.param.init(seed, 0, 1, LINEAR, ChannelIDs::ENCODER, [this] (float p) { setTrack3Pan(p); });
    track4.pan.param.init(seed, 0, 1, LINEAR, ChannelIDs::ENCODER, [this] (float p) { setTrack4Pan(p); });

    track1.track.initIO(t1);
    track2.track.initIO(t2);
    track3.track.initIO(t3);
    track4.track.initIO(t4);

    track1.pan.param.setIsSelected(true);
}

void Mixer::initFX(DaisySeed* seed, DelayLine<float, MAXDELAY>* t1[2], DelayLine<float, MAXDELAY>* t2[2], 
                                    DelayLine<float, MAXDELAY>* t3[2], DelayLine<float, MAXDELAY>* t4[2])
{
    track1.track.initFX(seed, t1);
    track2.track.initFX(seed, t2);
    track3.track.initFX(seed, t3);
    track4.track.initFX(seed, t4);
}

void Mixer::tick()
{
    track1.track.tick();
    track1.gain.param.tick();
    track1.pan.param.tick();

    track2.track.tick();
    track2.gain.param.tick();
    track2.pan.param.tick();

    track3.track.tick();
    track3.gain.param.tick();
    track3.pan.param.tick();

    track4.track.tick();
    track4.gain.param.tick();
    track4.pan.param.tick();

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
    }

    // pass mix buffer through limiter
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
        //mix[L][i] *= master.value;
        //mix[R][i] *= master.value;

        //limiter.ProcessBlock(&mix[L][i], size, 0.f);
        //limiter.ProcessBlock(&mix[R][i], size, 0.f);

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