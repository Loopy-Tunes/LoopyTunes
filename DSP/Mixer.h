/********************************************//**
 *  Class name: Mixer
 *  Function: Mixes outputs of track classes
 ***********************************************/

#include "Track.h"

class Mixer
{
public:

    void prepare();
    void processBlock(float* input, size_t size);

    void setTrack1Gain(float val) { track1.gain = val; }
    void setTrack2Gain(float val) { track2.gain = val; }
    void setTrack3Gain(float val) { track3.gain = val; }
    void setTrack4Gain(float val) { track4.gain = val; }

private:

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