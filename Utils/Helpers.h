#include "stddef.h"
#include <algorithm>

// channel IDs
enum ChannelIDs
{
    AMP1 = 0,
    AMP2,
    AMP3,
    AMP4,
    MASTER,
    ENCODER
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

// track I/O
struct TrackIO
{
    ChannelIDs amp;
    dsy_gpio_pin record;
    dsy_gpio_pin play;
};

// track state
enum TrackState
{
    RECORDING = 0,
    PLAYING,
    STOPPED
};

enum Funcs
{
    SINE = 0,
    TANH,
    SIGNUM
};

// curve types
enum CurveType
{
    LINEAR = 0,
    EXP
};