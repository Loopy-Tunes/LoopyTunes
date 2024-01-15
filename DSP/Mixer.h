/********************************************//**
 *  Class name: Mixer
 *  Function: Mixes outputs of track classes
 ***********************************************/

#include "Track.h"

class Mixer
{
public:

    void prepare();
    void init();

    void processBlock(float inputL, float inputR, float outputL, float outputR, size_t size);

    void setTrack1Gain(float val) { track1.gain = val; }
    void setTrack2Gain(float val) { track2.gain = val; }
    void setTrack3Gain(float val) { track3.gain = val; }
    void setTrack4Gain(float val) { track4.gain = val; }

    void setTrack1Record(bool val) { track1.track.setIsRecording(val); }
    void setTrack2Record(bool val) { track2.track.setIsRecording(val); }
    void setTrack3Record(bool val) { track3.track.setIsRecording(val); }
    void setTrack4Record(bool val) { track4.track.setIsRecording(val); }

    void setTrack1Play(bool val) { track1.track.setIsPlaying(val); }
    void setTrack2Play(bool val) { track2.track.setIsPlaying(val); }
    void setTrack3Play(bool val) { track3.track.setIsPlaying(val); }
    void setTrack4Play(bool val) { track4.track.setIsPlaying(val); }

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