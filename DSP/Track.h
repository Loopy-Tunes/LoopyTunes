#include "../Utils/Constants.h"
#include "../Parameters/AudioParameter.h"

/**********************************************************//**
 *  Class name: Track
 *  Function: Processes audio buffer and FX for each track
 *************************************************************/

class Track
{
public:

    void init();
   
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

    float DSY_SDRAM_BSS buffer[2][SAMPLERATE * DURATION];
    size_t bufferSize;

};