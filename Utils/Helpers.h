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
namespace ChannelIDs
{
    const uint8_t Amp1 = 0;
    const uint8_t Amp2 = 1;
    const uint8_t Amp3 = 2;
    const uint8_t Amp4 = 3;
    const uint8_t Encoder = 4;

    const uint8_t TEMP1 = 1;
    const uint8_t TEMP2 = 2;
    const uint8_t TEMP3 = 3;
    const uint8_t TEMP4 = 4;
};