#include "stddef.h"
#include <algorithm>

// ADC channelIDs
enum ChannelIDs
{
    AMP1 = 0,
    AMP2,
    AMP3,
    AMP4,
    MASTER
};

// playhead
struct Playhead
{
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

// track state
enum TrackState
{   
    RECORDING = 0,
    PLAYING,
    STOPPED
};

// curve types
enum CurveType
{
    LINEAR = 0,
    EXP
};