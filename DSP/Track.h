#include "../Utils/Constants.h"
#include "../Parameters/AudioParameter.h"

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
    void incrementWritePos();
    void incrementReadPos();

    void processInputBlock(const float* left, const float* right, size_t size);
    void processOutputBlock(float* left, float* right, size_t size);

private:

    Playhead ph;
    TrackInformation ti;

    float* buffer[2];
    size_t bufferSize;

};

