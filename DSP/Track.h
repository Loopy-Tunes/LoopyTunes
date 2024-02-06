#ifndef TRACK_H
#define TRACK_H

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

    void init(daisy::DaisySeed* seed, float* mem[2], dsy_gpio_pin r, dsy_gpio_pin p);
    void tick();

    void setIsRecording();
    void setIsPlaying();

    bool getIsRecording() { return ph.isRecording; }
    bool getIsPlaying() { return ph.isPlaying; }

    void incrementWritePos();
    void incrementReadPos();
    size_t getReadPos() { return ph.readPos; }

    void prepare();
    void processInputBlock(const float* left, const float* right, size_t size);
    void processOutputBlock(float* left, float* right, size_t size);

private:

    Playhead ph;
    TrackInformation ti;

    BinaryParameter record;
    BinaryParameter play;

    float* buffer[2];
    size_t bufferSize;

    Delay delay;
};

#endif