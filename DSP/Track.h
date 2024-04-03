#ifndef TRACK_H
#define TRACK_H

#include "FX/PitchShift.h"
#include "FX/Waveshaper.h"
#include "FX/Filter.h"
#include "FX/Delay.h"
#include "FX/Reverb/Reverb.h"
#include "../Parameters/BinaryParameter.h"
#include <utility>

/**********************************************************//**
 *  Class name: Track
 *  Function: Processes audio buffer and FX for each track
 *************************************************************/

class Track
{
public:

    void init(float* mem[2], int ID);
    void initIO(TrackIO io);
    void initFX(EncoderDriver* driver, DelayLine<float, MAXDELAY>* dl[2]);
    void tick();
    void clearBuffer();

    void setIsRecording();
    void setIsPlaying();

    TrackState getState() { return state; }

    void incrementWritePos();
    void incrementReadPos();
    size_t getReadPos() { return ph.readPos; }

    void processInputBlock(const float* left, const float* right, size_t size);
    void processOutputBlock(float* output[2], size_t size);

private:

    int trackID;

    TrackState state;
    Playhead ph;
    TrackInformation ti;

    BinaryParameter record;
    BinaryParameter play;

    float* buffer[2];
    size_t bufferSize;

    //PitchShift pitchShift;
    //Waveshaper shaper;
    //Filter filter;
    Delay delay;
    //Reverb reverb;
};

#endif