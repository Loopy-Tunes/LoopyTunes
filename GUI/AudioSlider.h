#ifndef AUDIOSLIDER_H
#define AUDIOSLIDER_H

#include "daisy_seed.h"
#include "FX/StyleSheet.h"
#include <string>

/********************************************************************//**
 *  Class name: AudioSlider
 *  Function: Slider class for representing the values of ADC channels
 ***********************************************************************/

using namespace daisy;

class AudioSlider
{
public:

    /***********************************************************************//**
    * @brief Initialises the instance
    * @param ID The channel ID of the ADC channel the slider is assigned to
    * @param seed A pointer to the hardware instance
    * @param uid A pointer to the LCD driver
    ***************************************************************************/
    void init(int ID, DaisySeed* seed, UiDriver* uid);

    /***********************************************************************//**
    * @brief Handles the updating of the slider
    ***************************************************************************/
    void tick();

    /***********************************************************************//**
    * @brief Handles the repainting of the slider on the screen
    * @param Index The channel index of the slider
    * @param selected If the channel is selected or not
    ***************************************************************************/
    void repaint(int index, bool selected);

private:

    DaisySeed* hw;
    UiDriver* lcd;

    float input;
    const float jitter = 0.01f;
    
    int channelID;
    bool isUpdated;
};

#endif