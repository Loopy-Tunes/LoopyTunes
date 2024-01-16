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

    void incrementPlayhead();

    float* getCurrentLeft() { return &buffer[L][ph.pos]; }
    float* getCurrentRight() { return &buffer[R][ph.pos]; }

    void setIsRecording(bool val) { ph.isRecording = val; }
    void setIsPlaying(bool val) { ph.isPlaying = val; }
    void resetPlayhead() { ph.pos = 0; }

private:

    Playhead ph;
    TrackInformation ti;

    float* buffer[2];
    size_t bufferSize;

    enum class State
    {
        EMPTY = 0,
        FULL
    };

};