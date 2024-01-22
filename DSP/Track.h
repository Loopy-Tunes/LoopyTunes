#include "Helpers.h"
#include "Constants.h"

/**********************************************************//**
 *  Class name: Track
 *  Function: Processes audio buffer and FX for each track
 *************************************************************/

class Track
{
public:

    void init(float* mem[2], const size_t s);
    
    void prepare();
    void processBlock(size_t size);
    void tick();

    void setIsRecording();
    void setIsPlaying();
    void incrementPlayhead();

    void processInput(const float* left, const float* right, size_t size);
    float* processOutputLeft();
    float* processOutputRight();

    float* getCurrentLeft() { return &buffer[L][ph.pos]; }
    float* getCurrentRight() { return &buffer[R][ph.pos]; }

private:

    Playhead ph;
    TrackInformation ti;

    float* buffer[2];
    size_t bufferSize;

    
};