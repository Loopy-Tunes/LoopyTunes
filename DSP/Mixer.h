#ifndef MIXER_H
#define MIXER_H

#include "Track.h"

/********************************************//**
 *  Class name: Mixer
 *  Function: Mixes outputs of track classes
 ***********************************************/

class Mixer
{
public:

    /*******************************************************************//**
    * @brief Initialises the mixer class
    * @param t1 An array of pointers pointing to the buffer for track 1
    * @param t2 An array of pointers pointing to the buffer for track 2
    * @param t3 An array of pointers pointing to the buffer for track 3
    * @param t4 An array of pointers pointing to the buffer for track 4
    ***********************************************************************/
    void init(DaisySeed* seed, float* t1[2], float* t2[2], float* t3[2], float* t4[2]); 

    /***********************************************************************//**
    * @brief Initialises the mixer channels
    * @param t1 An array of pointers pointing to the mix buffer for track 1
    * @param t2 An array of pointers pointing to the mix buffer for track 2
    * @param t3 An array of pointers pointing to the mix buffer for track 3
    * @param t4 An array of pointers pointing to the mix buffer for track 4
    ***************************************************************************/
    void initMixChannels(float* m[2], float* t1[2], float* t2[2], float* t3[2], float* t4[2]);

    /***********************************************************************//**
    * @brief Initialises all the effects
    * @param driver A pointer to the LCD driver 
    * @param t1 An array of pointers pointing to the delay line for track 1
    * @param t2 An array of pointers pointing to the delay line for track 2
    * @param t3 An array of pointers pointing to the delay line for track 3
    * @param t4 An array of pointers pointing to the delay line for track 4
    ***************************************************************************/
    void initFX(EncoderDriver* driver, DelayLine<float, MAXDELAY>* t1[2], DelayLine<float, MAXDELAY>* t2[2], 
                                       DelayLine<float, MAXDELAY>* t3[2], DelayLine<float, MAXDELAY>* t4[2]);
    /***********************************************************************//**
    * @brief Handles the updating of the backend parameters
    ***************************************************************************/
    void tick();
    /***********************************************************************//**
    * @brief Processes a block of samples from the Seed's input
    * @param left A pointer to the Seed's left input buffer
    * @param right A pointer to the Seed's right input buffer
    * @param size 
    ***************************************************************************/
    void processInputBlock(const float* left, const float* right, size_t size);
    /***********************************************************************//**
    * @brief Handles the panning of the mixer channels
    ***************************************************************************/
    void panChannels(size_t size);
    /***********************************************************************//**
    * @brief Handles the mixing of the output
    ***************************************************************************/
    void mixOutput(size_t size);
    /***********************************************************************//**
    * @brief Processes a block of samples and sends them to the Seed's output
    * @param left A pointer to the Seed's left output buffer
    * @param right A pointer to the Seed's right output buffer
    ***************************************************************************/
    void processOutputBlock(float* left, float* right, size_t size);
    /***********************************************************************//**
    * @brief Applies a -6dB linear taper pan to a mix buffer
    * @param buffer The mix buffer the panning should be applied to
    * @param pan The pan value for that mix buffer
    * @param size The size of the mix buffer
    ***************************************************************************/
    void panMixBuffer(float* buffer[2], float pan, size_t size);
    /***********************************************************************//**
    * @brief Sets the mix divisor used to mix the output
    ***************************************************************************/
    void setMixDiv();
    /***********************************************************************//**
    * @brief Sets the pan value for track 1
    ***************************************************************************/
    void setTrack1Pan(float p){ track1.pan.value = p; }
    /***********************************************************************//**
    * @brief Sets the pan value for track 2
    ***************************************************************************/
    void setTrack2Pan(float p){ track2.pan.value = p; }
    /***********************************************************************//**
    * @brief Sets the pan value for track 3
    ***************************************************************************/
    void setTrack3Pan(float p){ track3.pan.value = p; }
    /***********************************************************************//**
    * @brief Sets the pan value for track 4
    ***************************************************************************/
    void setTrack4Pan(float p){ track4.pan.value = p; }
    /***********************************************************************//**
    * @brief Sets the gain value for track 1
    ***************************************************************************/
    void setTrack1Gain(float g){ track1.gain.value = g; }
    /***********************************************************************//**
    * @brief Sets the gain value for track 2
    ***************************************************************************/
    void setTrack2Gain(float g){ track2.gain.value = g; }
    /***********************************************************************//**
    * @brief Sets the gain value for track 3
    ***************************************************************************/
    void setTrack3Gain(float g){ track3.gain.value = g; }
    /***********************************************************************//**
    * @brief Sets the gain value for track 4
    ***************************************************************************/
    void setTrack4Gain(float g){ track4.gain.value = g; }
    /***********************************************************************//**
    * @brief Sets the master gain value
    ***************************************************************************/
    void setMasterVolume(float m){ master.value = m; }

private:

    struct MixerChannel
    {
        Track track;
        float* buffer[2];
        AudioParameterWrapper<float> pan;
        AudioParameterWrapper<float> gain;

        inline float getCurVal(int chan, size_t index)
        {
            if(gain.value < 0.005 || track.getState() == STOPPED)
                return 0.0f;
            else
                return buffer[chan][index] * gain.value;
        }
    };

    MixerChannel track1;
    MixerChannel track2;
    MixerChannel track3;
    MixerChannel track4;

    int mixDiv;
    AudioParameterWrapper<float> master;
    float* mix[2];
    size_t bufferSize;
};

#endif