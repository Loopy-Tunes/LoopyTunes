#include "stddef.h"
#include <algorithm>

// ADC Channel IDs
/***********************************************************************//**
* @brief Represents the channel IDs for easy assignment and access
***************************************************************************/
enum ChannelIDs
{
    AMP1 = 0,
    AMP2,
    AMP3,
    AMP4,
    MASTER
};

// Track information
/***********************************************************************//**
* @brief Struct definition for storing track information
***************************************************************************/
struct TrackInformation
{
    bool isEmpty;
    size_t loopLength;
};

// Track state
/***********************************************************************//**
* @brief Struct definition for monitoring track state
***************************************************************************/
enum TrackState
{   
    RECORDING = 0,
    PLAYING,
    STOPPED
};

// Curve types
/***********************************************************************//**
* @brief Struct definition for types of curve used to process values
***************************************************************************/
enum CurveType
{
    LINEAR = 0,
    EXP
};