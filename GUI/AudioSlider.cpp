#include "AudioSlider.h"
#include "../Drivers/daisy_ILI9341.hpp"

void AudioSlider::init(int ID, DaisySeed* seed)
{
    hw = seed;

    input = 0;

    channelID = ID;
    isUpdated = true;
}

void AudioSlider::tick()
{
    float newInput = hw->adc.GetFloat(channelID);
    if(newInput > (input + jitter) || newInput < (input - jitter))
    {
        input = newInput;
        isUpdated = true;
    }
}

void AudioSlider::repaint(int index, bool selected)
{
    if(isUpdated)
    {
        int bar_x = StyleSheet::Mixer::firstFaderX + (index) * (StyleSheet::Mixer::faderWidth + StyleSheet::Mixer::faderSpacing);
        int bar_height = static_cast<int>(input * StyleSheet::Mixer::faderHeight);
        int bar_top = StyleSheet::Mixer::mixerBottom - bar_height;

        // Clear the fader area
        lcd.FillRect(Rectangle(bar_x, StyleSheet::Mixer::mixerBottom - StyleSheet::Mixer::faderHeight, StyleSheet::Mixer::faderWidth, StyleSheet::Mixer::faderHeight), COLOR_BLACK);

        uint16_t color = selected ? COLOR_GREEN : COLOR_BLUE;

        // Draw the fader bar with the new height
        lcd.FillRect(Rectangle(bar_x, bar_top, StyleSheet::Mixer::faderWidth, bar_height), color);

        // Write the channel number underneath the bar
        lcd.WriteString(std::to_string(channelID).c_str(), bar_x + (StyleSheet::Mixer::faderWidth / 2) - 5, StyleSheet::Mixer::mixerBottom + 10, Font_7x10, StyleSheet::Mixer::textColor);
    
        isUpdated = false;
    }
}