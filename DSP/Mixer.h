#include "Track.h"

/********************************************//**
 *  Class name: Mixer
 *  Function: Mixes outputs of track classes
 ***********************************************/

class Mixer
{
public:

    void init(daisy::DaisySeed* seed, float* t1[2], float* t2[2], float* t3[2], float* t4[2]); 
    void initParameters();
    
    void prepare();
    void tick();

    void processInputBlock(const float* left, const float* right, size_t size);
    void processOutputBlock(float* left, float* right, size_t size);

    void setIsRecording() { track1.track.setIsRecording(); }
    void setIsPlaying() { track1.track.setIsPlaying(); }

private:

    struct MixerTrack
    {
        Track track;
        AudioParameter<float> gain;
    };

    MixerTrack track1;
    MixerTrack track2;
    MixerTrack track3;
    MixerTrack track4;

    static float DSY_SDRAM_BSS mix[2][SAMPLERATE * DURATION];
    size_t bufferSize;

};