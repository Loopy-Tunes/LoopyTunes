#include "stddef.h"
#include <algorithm>

// playhead
struct Playhead
{
    bool isRecording;
    bool wasRecording;
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

// curve types
enum CurveType
{
    LINEAR = 0,
    EXP
};

// channel IDs
enum ChannelIDs
{
    AMP1 = 0,
    TEMP1,
    TEMP2,
    TEMP3,
    TEMP4,
    ENCODER
};