#include "Track.h"

/********************************************//**
 *  Class name: Mixer
 *  Function: Mixes outputs of track classes
 ***********************************************/

class Mixer
{
public:

    void init(float* m, float* t1, float* t2, float* t3, float* t4, size_t s); // pointers to tracks, buffer sizes
    
    void prepare();
    void processBlock(size_t size);

private:

    float* buffer;
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