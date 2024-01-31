#include "../Utils/Constants.h"
#include "Delay.h"
#include <utility>

/**********************************************************//**
 *  Class name: Track
 *  Function: Processes audio buffer and FX for each track
 *************************************************************/

class Track
{
public:

    void init(float* mem[2]);
   
    void prepare();
    void tick();

    void setIsRecording();
    void setIsPlaying();

    bool getIsRecording() { return ph.isRecording; }
    bool getIsPlaying() { return ph.isPlaying; }

    void incrementWritePos();
    void incrementReadPos();

    void processInputBlock(const float* left, const float* right, size_t size);
    std::pair<float*, float*> processOutput();

private:

    Playhead ph;
    TrackInformation ti;

    float* buffer[2];
    size_t bufferSize;
};

