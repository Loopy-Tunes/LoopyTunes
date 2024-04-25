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

    void init(EncoderDriver* ed, UiDriver* uid, std::function<void()> bypassCallback)
    {
        encoder = ed;
        lcd = uid;

        callback = bypassCallback;
        isSelected = false;
        isBypassed = true;
    }

    void tick()
    {
        if(isSelected && encoder->getButtonState())
        {
            callback();
            isBypassed = !isBypassed;
        }
    }

    void repaint()
    {
        // Draw on/off button for Bypass
        uint16_t bypassButtonY = StyleSheet::Effects::headerHeight + 15; ///
        uint16_t buttonColor = isBypassed? COLOR_GREEN : COLOR_RED;
        Rectangle bypassButtonRect(10, bypassButtonY, StyleSheet::Effects::bypassButtonWidth, StyleSheet::Effects::bypassButtonHeight); ///
        lcd->FillRect(bypassButtonRect, buttonColor);
        lcd->DrawRect(bypassButtonRect, StyleSheet::Effects::borderColor);
        lcd->WriteString(isBypassed ? "On" : "Off", 20, StyleSheet::Effects::headerHeight + 20, Font_11x18, StyleSheet::Effects::textColor);
    }

    void setIsSelected(bool state) { isSelected = state; } // called when the bypass button is selected

private:

    EncoderDriver* encoder;
    UiDriver* lcd;

    std::function<void()> callback;
    bool isSelected;
    bool isBypassed;
};

#endif