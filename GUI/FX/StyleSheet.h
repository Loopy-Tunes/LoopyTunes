#ifndef STYLESHEET_H
#define STYLESHEET_H

#include "../../Drivers/daisy_ILI9341.hpp"

namespace StyleSheet
{
    namespace Mixer
    {
        const static int screenWidth = 320; 
        const static int screenHeight = 240; 
        const static int faderWidth = 30;
        const static int faderHeight = 100;
        const static int faderSpacing = 35; 
        const static int firstFaderX = (screenWidth - (faderWidth * 4 + faderSpacing * 3)) / 2; 
        const static int mixerBottom = 180; 
        const static uint16_t frameColor = COLOR_CYAN;
        const static uint16_t textColor = COLOR_WHITE;
        const static int frameThickness = 2; 
    }

    namespace Tracks
    {
        static uint16_t borderColor = COLOR_CYAN;
        static uint16_t text_color = COLOR_WHITE;
        static uint16_t effectBoxColor = COLOR_BLACK;
        static uint16_t selectedEffectColor = COLOR_GREEN;
        
        // Define fonts
        static const FontDef& smallerFont = Font_7x10; 
        static const FontDef& largerFont = Font_16x26; 
        static const int smallerFontHeight = 10; 

        // Define the display dimensions
        static const int displayWidth = 320; 
        static const int displayHeight = 240; 

        // Top position for effect boxes
        static int effectsYStart = 96; 
    }

    namespace Effects
    {
        const static uint16_t screenWidth = 320;
        const static uint16_t screenHeight = 240;
        const static uint16_t borderColor = COLOR_CYAN;
        const static uint16_t textColor = COLOR_CYAN;
        const static uint16_t sliderBackColor = COLOR_BLACK;
        const static uint16_t headerHeight = 50;
        const static uint16_t paramSpacing = 35; // Adjust spacing as needed
        const static uint16_t sliderHeight = 20; // Adjust height as needed
        const static uint16_t sliderWidth = 180; // Slider width
        const static uint16_t frameThickness = 2;
        const static uint16_t sliderOffsetX = 130; // X position for sliders
        const static uint16_t bypassButtonWidth = 60;
        const static uint16_t bypassButtonHeight = 30;
    }
}

#endif