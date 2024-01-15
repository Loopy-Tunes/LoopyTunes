#include "stddef.h"
#include <algorithm>

// playhead
struct Playhead
{
    bool isRecording;
    bool isPlaying;
    size_t pos;
};

// stereo buffer
struct StereoBuffer
{
    float left;
    float right;
    size_t size;
/*
    void init() 
    { 
        std::fill(&left[0], &left[size - 1], 0); 
        std::fill(&right[0], &right[size - 1], 0); 
    }
*/
};