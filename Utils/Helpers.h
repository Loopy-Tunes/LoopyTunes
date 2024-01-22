#include "stddef.h"
#include <algorithm>

// playhead
struct Playhead
{
    bool isRecording;
    bool isPlaying;
    size_t writePos;
    size_t readPos;

    void reset() 
    { 
        writePos = 0;
        readPos = 0; 
    }
};

// track information
struct TrackInformation
{
    bool isEmpty;
    size_t loopLength;
};