#include "Helpers.h"

/**********************************************************//**
 *  Class name: Track
 *  Function: Processes audio buffer and FX for each track
 *************************************************************/

class Track
{
public:

    void prepare();
    void init(float *memL, float *memR, size_t buffSize);
    
    void processBlock(float inputL, float inputR, float outputL, float outputR, size_t size);

    void setIsRecording(bool val) { ph.isRecording = val; }
    void setIsPlaying(bool val) { ph.isPlaying = val; }
    void setPos(size_t newPos) { ph.pos = newPos; }
    void resetPos() { ph.pos = 0; }

private:

    Playhead ph;
    StereoBuffer buffer;
    //float DSY_SDRAM_BSS buffer[2]

    enum class State
    {
        EMPTY = 0,
        FULL
    };

};