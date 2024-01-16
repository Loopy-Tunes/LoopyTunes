#include "stddef.h"
#include <algorithm>

// playhead
struct Playhead
{
    bool isRecording;
    bool isPlaying;
    size_t pos;
};

// track information
struct TrackInformation
{
    size_t loopLength;
};