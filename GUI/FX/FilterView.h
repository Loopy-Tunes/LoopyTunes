#ifndef FILTERVIEW_H
#define FILTERVIEW_H

#include "SteppedSlider.h"

/*************************************************//**
 *  Class name: FilterView
 *  Function: FX level GUI class for the filter
 ****************************************************/

class FilterView
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
    SteppedSlider mode;
    SteppedSlider frequency;
    SteppedSlider resonance;

    int numberOfParameters = 3;
    const char* parameterNames[3] = {"Mode", "Frequency", "Resonance"};
    int currentParam = 0;

    bool isOpen;
    bool isPainted;
    int bypassIndexes[4] = {2, 7, 12, 17};
};

#endif