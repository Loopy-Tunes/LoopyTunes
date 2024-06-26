#ifndef PITCHSHIFTIEW_H
#define PITCHSHIFTVIEW_H

#include "SteppedSlider.h"

/*************************************************//**
 *  Class name: PitchShiftView
 *  Function: FX level GUI class for the pitch shift
 ****************************************************/

class PitchShiftView
{
public:


    /***********************************************************************//**
    * @brief Initialises the instance
    * @param ID The ID of the track view the instance belongs to
    * @param encoder A pointer to the encoder driver
    * @param kpd A pointer to the keypad driver
    ***************************************************************************/
    void init(int ID, EncoderDriver* driver, KeypadDriver* kpd);
    
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
    * @brief Sets the currently selected parameter on the LCD
    ***************************************************************************/
    void setCurrentParam(int newParam) { currentParam = newParam; }

private:

    int trackID;

    KeypadDriver* keypad;

    BypassButton bypass;
    SteppedSlider amount;
    SteppedSlider semitones;

    int numberOfParameters = 2;
    const char* parameterNames[2] = {"Amount", "Semitones"};
    int currentParam = 0;

    bool isOpen;
    bool isPainted;
    int bypassIndexes[4] = {0, 5, 10, 15};
};

#endif