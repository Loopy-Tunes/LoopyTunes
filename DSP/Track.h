#ifndef TRACK_H
#define TRACK_H

#include "FX/Waveshaper.h"
#include "FX/Delay.h"
#include "../Parameters/BinaryParameter.h"
#include <utility>

/**********************************************************//**
 *  Class name: Track
 *  Function: Processes audio buffer and FX for each track
 *************************************************************/

class Track
{
public:

    void init(float* mem[2]);
    void initIO(TrackIO io);
    void initFX(DaisySeed* seed, DelayLine<float, MAXDELAY>* dl[2]);
    void tick();
    void clearBuffer();

    void setIsRecording();
    void setIsPlaying();

    TrackState getState() { return state; }

    void incrementWritePos();
    void incrementReadPos();
    size_t getReadPos() { return ph.readPos; }

    void prepare();
    void processInputBlock(const float* left, const float* right, size_t size);
    void processOutputBlock(float* left, float* right, size_t size);

private:

    TrackState state;
    Playhead ph;
    TrackInformation ti;

    BinaryParameter record;
    BinaryParameter play;

    float* buffer[2];
    size_t bufferSize;

    Waveshaper shaper;
    Delay delay;
};

#endif