#include "FilterView.h"
#include "../../Drivers/daisy_ILI9341.hpp"

void FilterView::init(int ID, EncoderDriver* driver, KeypadDriver* kpd)
{
    trackID = ID;

    keypad = kpd;

    bypass.init(driver, driver->getBypassCallback(bypassIndexes[ID-1]));
    mode.init(trackID + ParameterIDs::Filter::mode, driver);
    frequency.init(trackID + ParameterIDs::Filter::frequency, driver);
    resonance.init(trackID + ParameterIDs::Filter::resonance, driver);

    isOpen = false;
    isPainted = false;
}

void FilterView::tick()
{
    mode.tick();
    frequency.tick();
    resonance.tick();

    if(isOpen)
        repaint();
}

void FilterView::repaint()
{
    if(!isPainted)
    {
        // Screen border
        lcd.DrawRect(Rectangle(StyleSheet::Effects::frameThickness, StyleSheet::Effects::frameThickness, StyleSheet::Effects::screenWidth - (2 * StyleSheet::Effects::frameThickness), StyleSheet::Effects::screenHeight - (2 * StyleSheet::Effects::frameThickness)), StyleSheet::Effects::borderColor);

        // Header and effect name
        char headerText[50];
        snprintf(headerText, sizeof(headerText), "Track %d-%s", trackID, "Filter");
        lcd.DrawRect(Rectangle(10, 10, StyleSheet::Effects::screenWidth - 20, StyleSheet::Effects::headerHeight), StyleSheet::Effects::borderColor);
        lcd.WriteString(headerText, 15, 15, Font_16x26, StyleSheet::Effects::textColor);

        uint16_t bypassButtonY = StyleSheet::Effects::headerHeight + 15; ///
        Rectangle bypassButtonRect(10, bypassButtonY, StyleSheet::Effects::bypassButtonWidth, StyleSheet::Effects::bypassButtonHeight);
        uint16_t startY = bypassButtonRect.GetY() + StyleSheet::Effects::bypassButtonHeight + 30; 

        bypass.repaint();

        // Draw parameters for the selected effect
        for (int i = 0; parameterNames[i] != nullptr; ++i) 
        {
            uint16_t paramY = startY + (i * StyleSheet::Effects::paramSpacing);
            lcd.WriteString(parameterNames[i], 10, paramY + 5, Font_7x10, StyleSheet::Effects::textColor);

            // Draw slider for the parameter value
            Rectangle sliderRect(StyleSheet::Effects::sliderOffsetX, paramY, StyleSheet::Effects::sliderWidth, StyleSheet::Effects::sliderHeight);
            //Rectangle sliderRect(screenWidth - sliderWidth - 10, paramY, sliderWidth, sliderHeight);
            lcd.FillRect(sliderRect, StyleSheet::Effects::sliderBackColor);
            // Slider foreground representing the actual parameter value (this part is just for illustration)
            lcd.FillRect(Rectangle(StyleSheet::Effects::sliderOffsetX, paramY, StyleSheet::Effects::sliderWidth * 0.5, StyleSheet::Effects::sliderHeight), (i == currentParam) ? COLOR_GREEN : COLOR_BLUE); // Assume 50% value for illustration
            // Slider border
            lcd.DrawRect(Rectangle(StyleSheet::Effects::sliderOffsetX, paramY, StyleSheet::Effects::sliderWidth, StyleSheet::Effects::sliderHeight), (i == currentParam) ? COLOR_GREEN : COLOR_BLUE);
        }

        isPainted = true;
    }
}

void FilterView::clear()
{

}