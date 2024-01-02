/********************************************//**
 *  Class name: Mixer
 *  Function: Mixes outputs of track classes
 ***********************************************/

#include "Track.h"

class Mixer
{
public:

    void prepare();
    void processBlock(float* input, float* output);

    void setTrack1Gain(float val);
    void setTrack2Gain(float val);
    void setTrack3Gain(float val);
    void setTrack4Gain(float val);

private:

    Track track1;
    Track track2;
    Track track3;
    Track track4;

};