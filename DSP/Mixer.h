#ifndef MIXER_H
#define MIXER_H

#include "Track.h"

/********************************************//**
 *  Class name: Mixer
 *  Function: Mixes outputs of track classes
 ***********************************************/

class Mixer
{
public:

    void init(DaisySeed* seed, float* m[2], float* t1[2], float* t2[2], float* t3[2], float* t4[2], DelayLine<float, MAXDELAY>* dl[2]); 
    void tick();

    void prepare();
    void processInputBlock(const float* left, const float* right, size_t size);
    void mixOutput();
    void processOutputBlock(float* left, float* right, size_t size);

    void setIsRecording() { track1.track.setIsRecording(); }
    void setIsPlaying() { track1.track.setIsPlaying(); }

    void setMasterVolume(float m){ master.value = m; }
    void setTrack1Gain(float g){ track1.gain.value = g; }
    void setTrack2Gain(float g){ track2.gain.value = g; }
    void setTrack3Gain(float g){ track3.gain.value = g; }
    void setTrack4Gain(float g){ track4.gain.value = g; }

private:

    AudioParameterWrapper<float> master;

    struct MixerChannel
    {
        Track track;
        float* buffer[2];
        AudioParameterWrapper<float> gain;
    };

    MixerChannel track1;
    MixerChannel track2;
    MixerChannel track3;
    MixerChannel track4;

    float* mix[2];
    size_t bufferSize;
};

#endif