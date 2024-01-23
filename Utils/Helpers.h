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

// curve types
enum CurveType
{
    LINEAR = 0,
    EXP
};

// channel IDs
struct ChannelIDs
{
    uint8_t Amp1;
    uint8_t Amp2;
    uint8_t Amp3;
    uint8_t Amp4;
    uint8_t Encoder;
};