#include "stddef.h"

/**********************************************************//**
 *  Class name: Track
 *  Function: Processes audio buffer and FX for each track
 *************************************************************/

class Track
{
public:

    void prepare();
    void processBlock(float* input, size_t size);

    void setIsRecording(bool val) { ph.isRecording = val; }
    void setIsPlaying(bool val) { ph.isPlaying = val; }

private:

    // playhead
    struct Playhead
    {
        bool isRecording;
        bool isPlaying;
        size_t pos;
    } ph;

    // track buffer
    struct TrackBuffer
    {
        float *buffer;
        size_t size;
    } trackBuff;

};