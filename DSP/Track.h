#ifndef TRACK_H
#define TRACK_H

#include "FX/Delay.h"
#include <utility>

/**********************************************************//**
 *  Class name: Track
 *  Function: Processes audio buffer and FX for each track
 *************************************************************/

class Track
{
public:

    void init(float* mem[2]);
    void tick();

    void setIsRecording();
    void setIsPlaying();

    bool getIsRecording() { return ph.isRecording; }
    bool getIsPlaying() { return ph.isPlaying; }

    void incrementWritePos();
    void incrementReadPos();

    void prepare();
    void processInputBlock(const float* left, const float* right, size_t size);
    std::pair<float*, float*> processOutput();

private:

    Playhead ph;
    TrackInformation ti;

    float* buffer[2];
    size_t bufferSize;
};

#endif