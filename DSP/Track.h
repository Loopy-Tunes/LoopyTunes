#include "Helpers.h"
#include "Constants.h"

/**********************************************************//**
 *  Class name: Track
 *  Function: Processes audio buffer and FX for each track
 *************************************************************/

class Track
{
public:

    void init(float* mem, const size_t s);
    
    void prepare();
    void processBlock(size_t size);

    void setIsRecording(bool val) { ph.isRecording = val; }
    void setIsPlaying(bool val) { ph.isPlaying = val; }
    void setPos(size_t newPos) { ph.pos = newPos; }
    void resetPos() { ph.pos = 0; }

private:

    Playhead ph;
    TrackInformation ti;

    float* buffer;
    size_t bufferSize;

    enum class State
    {
        EMPTY = 0,
        FULL
    };

};