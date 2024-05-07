#ifndef BYPASSBUTTON_H
#define BYPASSBUTTON_H

#include "../../Drivers/EncoderDriver.h"
#include "StyleSheet.h"

/********************************************************//**
 *  Class name: BypassButton
 *  Function: Button used for bypassing an effect
 ***********************************************************/

class BypassButton 
{
public:

    /***********************************************************************//**
    * @brief Initialises the instance
    * @param ed A pointer to the encoder driver
    * @param bypassCallback The function to be called when the bypass is set
    ***************************************************************************/
    void init(EncoderDriver* ed, std::function<void()> bypassCallback)
    {
        encoder = ed;

        callback = bypassCallback;
        isSelected = false;
        isBypassed = true;
    }

    /***********************************************************************//**
    * @brief Checks if the bypass state needs to be changed
    ***************************************************************************/
    void tick()
    {
        if(isSelected && encoder->getButtonState())
        {
            callback();
            isBypassed = !isBypassed;
        }
    }

    /***********************************************************************//**
    * @brief Handles the repainting of the button
    ***************************************************************************/
    void repaint()
    {
        // Draw on/off button for Bypass
        uint16_t bypassButtonY = StyleSheet::Effects::headerHeight + 15; ///
        uint16_t buttonColor = isBypassed? COLOR_GREEN : COLOR_RED;
        Rectangle bypassButtonRect(10, bypassButtonY, StyleSheet::Effects::bypassButtonWidth, StyleSheet::Effects::bypassButtonHeight); ///
        lcd.FillRect(bypassButtonRect, buttonColor);
        lcd.DrawRect(bypassButtonRect, StyleSheet::Effects::borderColor);
        lcd.WriteString(isBypassed ? "On" : "Off", 20, StyleSheet::Effects::headerHeight + 20, Font_11x18, StyleSheet::Effects::textColor);
    }

    /***********************************************************************//**
    * @brief Sets if the button is selected on the interface
    * @param state Sets the bypass state of the instance
    ***************************************************************************/
    void setIsSelected(bool state) { isSelected = state; } // called when the bypass button is selected

private:

    EncoderDriver* encoder;

    std::function<void()> callback;
    bool isSelected;
    bool isBypassed;
};

#endif