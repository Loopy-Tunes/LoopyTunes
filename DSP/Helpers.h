#include "stddef.h"
#include <algorithm>

// playhead
struct Playhead
{
    bool isRecording;
    bool isPlaying;
    size_t pos;

    void reset() { pos = 0; }
};

// track information
struct TrackInformation
{
    size_t loopLength;
};