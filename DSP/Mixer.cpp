#include "Mixer.h"

void Mixer::init(DaisySeed* seed, float* m[2], float* t1[2], float* t2[2], float* t3[2], float* t4[2], DelayLine<float, MAXDELAY>* dl[2])
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
    track1.gain.param.init(seed, 0, 1, LINEAR, t1.amp, [this] (float g) { setTrack1Gain(g); });
    track2.gain.param.init(seed, 0, 1, LINEAR, t2.amp, [this] (float g) { setTrack2Gain(g); });
    track3.gain.param.init(seed, 0, 1, LINEAR, t3.amp, [this] (float g) { setTrack3Gain(g); });
    track4.gain.param.init(seed, 0, 1, LINEAR, t4.amp, [this] (float g) { setTrack4Gain(g); });

    track1.track.initIO(t1);
    track2.track.initIO(t2);
    track3.track.initIO(t3);
    track4.track.initIO(t4);
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

void Mixer::prepare()
{

}

void Mixer::processInputBlock(const float* left, const float* right, size_t size)
{
    track1.track.processInputBlock(left, right, size);
    track2.track.processInputBlock(left, right, size);
    track3.track.processInputBlock(left, right, size);
    track4.track.processInputBlock(left, right, size);
}

void Mixer::panTrack(float* buffer[2], size_t size)
{
    /*
        LeftOut  = (1-pan) * MonoIn // = power((1-pan),1) * MonoIn;
        RightOut = pan * MonoIn
    */

   
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
    track1.track.processOutputBlock(track1.buffer[L], track1.buffer[R], size);
    track2.track.processOutputBlock(track2.buffer[L], track2.buffer[R], size);
    track3.track.processOutputBlock(track3.buffer[L], track3.buffer[R], size);
    track4.track.processOutputBlock(track4.buffer[L], track4.buffer[R], size);

    mixOutput(size);

    for(size_t i = 0 ; i < size ; i++)
    {
        left[i] = mix[L][i] * master.value;
        right[i] = mix[R][i] * master.value;
    }
}