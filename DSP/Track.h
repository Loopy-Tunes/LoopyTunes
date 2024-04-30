#ifndef TRACK_H
#define TRACK_H

#include "FX/PitchShift.h"
#include "FX/Waveshaper.h"
#include "FX/Filter.h"
#include "FX/Delay.h"
#include "FX/Reverb/Reverb.h"
#include "../Parameters/AudioParameter.h"
#include "../Parameters/BinaryParameter.h"
#include <utility>

/**********************************************************//**
 *  Class name: Track
 *  Function: Processes audio buffer and FX for each track
 *************************************************************/

class Track
{
public:

    /*************************************************************************************************//**
    * @brief Initialises the instance
    * @param mem An array of pointers pointing to the track's buffers in the Buffers namespace
    * @param ID The track ID used to initialise its parameters
    * @param r The pin number of the track's record button used to initialise the record BinaryParameter
    * @param p The pin number of the track's play button used to initialise the play BinaryParameter
    *****************************************************************************************************/
    void init(float* mem[2], int ID, dsy_gpio_pin r, dsy_gpio_pin p);

    /***************************************************************************************//**
    * @brief Initialise the track's effects
    * @param driver A pointer to the LCD driver that lives in LoopyTunes 
    * @param dl An array of points pointing to the track's delay lines in the Buffers namespace
    *******************************************************************************************/
    void initFX(EncoderDriver* driver, DelayLine<float, MAXDELAY>* dl[2]);

    /*******************************************************************//**
    * @brief Handles the updating of the instance's branch in the hierarchy
    ***********************************************************************/
    void tick();

    /*******************************************************************//**
    * @brief Sets all values in the track's assigned buffer to 0
    ***********************************************************************/
    void resetBuffer();

    /*******************************************************************//**
    * @brief Sets the track's recording state
    ***********************************************************************/
    void setIsRecording();

    /*******************************************************************//**
    * @brief Sets the track's playing state
    ***********************************************************************/
    void setIsPlaying();

    /*******************************************************************//**
    * @brief Gets the current state of the track
    * @return The state of the track
    ***********************************************************************/
    TrackState getState() { return state; }

    /*******************************************************************//**
    * @brief Increments the track's playhead write position for recording
    ***********************************************************************/
    void incrementWritePos();

    /*******************************************************************//**
    * @brief Increments the track's playhead's read position for playback
    ***********************************************************************/
    void incrementReadPos();

    /*******************************************************************//**
    * @brief Gets the current value of the track's playhead's read position
    ***********************************************************************/
    size_t getReadPos() { return ph.readPos; }

    /**********************************************************************//**
    * @brief Processes a block of samples from the Seed's input
    * @param left A pointer to the Seed's left input buffer
    * @param right A pointer to the Seed's right input buffer
    * @param size the Size of the block of samples that need to be processed
    **************************************************************************/
    void processInputBlock(const float* left, const float* right, size_t size);

    /***********************************************************************************//**
    * @brief Fills the track's mix buffer with samples and processes it through the effects
    * @param output An array of pointers to the track's mix buffer
    * @param size The number of samples to process
    ***************************************************************************************/
    void processOutputBlock(float* output[2], size_t size);

private:

    /***********************************************************************//**
    * @brief Sets the start position in samples for the seamless looping system
    ***************************************************************************/
    void setLoopStart()
    {
        startPos = bufferSize - ((startPos * SAMPLERATE) / 1000);
    }
    /*******************************************************************//**
    * @brief Interpolates the sample value for the seamless looping system
    * @param input The sample that needs to be calculated
    * @param channel The channel the sample belongs to
    * @return The interpolated sample
    ***********************************************************************/
    inline float calculateLoop(float input, int channel)
    {
        float d1 = bufferSize - ph.readPos;
        float d2 = startPos + ph.readPos;
        float sample = ((input * d1) + (buffer[channel][0] * d2)) / (d1 + d2);

        return sample;
    }

    int trackID;

    TrackState state;
    struct Playhead
    {
        size_t writePos;
        size_t readPos;

        void reset() 
        { 
            writePos = 0;
            readPos = 0; 
        }
    } ph;
    TrackInformation ti;

    BinaryParameter record;
    BinaryParameter play;

    float* buffer[2];
    size_t bufferSize;

    float loopStart;
    float startPos;

    PitchShift pitchShift;
    Waveshaper shaper;
    Filter filter;
    Delay delay;
    Reverb reverb;
};

#endif