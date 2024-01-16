#include "Track.h"

/********************************************//**
 *  Class name: Mixer
 *  Function: Mixes outputs of track classes
 ***********************************************/

class Mixer
{
public:

    void init(float* m[2], float* t1[2], float* t2[2], float* t3[2], float* t4[2], size_t s); // pointers to tracks, buffer sizes
    
    void prepare();
    void processBlock(size_t size);

private:

    float* buffer[2];
    size_t bufferSize;

    struct MixerTrack
    {
        Track track;
        float gain;
    };

    MixerTrack track1;
    MixerTrack track2;
    MixerTrack track3;
    MixerTrack track4;

};