#ifndef MIXERVIEW_H
#define MIXERVIEW_H

#include "AudioSlider.h"
#include "TrackView.h"

/********************************************//**
 *  Class name: MixerView
 *  Function: Top level GUI class 
 ***********************************************/

class MixerView
{
public:

    /***********************************************************************//**
    * @brief Initialises the mixer view and all other GUI classes
    * @param seed A pointer to the hardware instance
    * @param encoder A pointer to the encoder driver
    * @param uid A pointer to the LCD driver
    * @param kpd A pointer to the keypad driver
    ***************************************************************************/
    void init(DaisySeed* seed, EncoderDriver* encoder, UiDriver* uid, KeypadDriver* kpd);

    /***********************************************************************//**
    * @brief Handles the updating of the view
    ***************************************************************************/
    void tick();

    /***********************************************************************//**
    * @brief Handles the repainting of the view
    ***************************************************************************/
    void repaint();

    /***********************************************************************//**
    * @brief Handles the clearing of the view
    ***************************************************************************/
    void clear();

    /***********************************************************************//**
    * @brief Sets if the view is currently open
    ***************************************************************************/
    void setIsOpen(bool state) { isOpen = state; }

    /***********************************************************************//**
    * @brief Sets if the view has been painted or not
    ***************************************************************************/
    void setIsPainted(bool state) { isPainted = state; }

    /***********************************************************************//**
    * @brief Sets which channel is currently selected
    * @param channel The channel to be selected
    ***************************************************************************/
    void setSelectedChannel(int channel) { selectedChannel = channel; }

private:

    UiDriver* lcd;
    KeypadDriver* keypad;

    AudioSlider amp1;
    AudioSlider amp2;
    AudioSlider amp3;
    AudioSlider amp4;

    int selectedChannel;
    std::array<AudioSlider, 4> ampSliders = {amp1, amp2, amp3, amp4};

    TrackView track1;
    TrackView track2;
    TrackView track3;
    TrackView track4;

    bool isOpen;
    bool isPainted;
};

#endif