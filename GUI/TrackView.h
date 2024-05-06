#ifndef TRACKVIEW_H
#define TRACKVIEW_H

#include "../Parameters/ParameterIDs.h"
#include "FX/PitchShiftView.h"
#include "FX/WaveshaperView.h"
#include "FX/FilterView.h"
#include "FX/ReverbView.h"
#include "FX/DelayView.h"

/********************************************//**
 *  Class name: TrackView
 *  Function: Track level GUI class
 ***********************************************/

class TrackView
{
public:

    /***********************************************************************//**
    * @brief Initialises the instance
    * @param seed A pointer to the hardware instance
    * @param encoder A pointer to the encoder driver
    * @param kpd A pointer to the keypad driver
    ***************************************************************************/
    void init(int ID, EncoderDriver* driver,  KeypadDriver* kpd);
    
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

private:

    int trackID;

    //static UiDriver* lcd;
    KeypadDriver* keypad;

    PitchShiftView pitchShiftView;
    WaveshaperView waveshaperView;
    FilterView filterView;
    ReverbView reverbView;
    DelayView delayView;

    int selectedEffectIndex;

    bool isOpen;
    bool isPainted;
};

#endif