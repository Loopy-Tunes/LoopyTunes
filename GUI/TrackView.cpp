#include "TrackView.h"

void TrackView::init(int ID, EncoderDriver* driver, UiDriver* uid, KeypadDriver* kpd)
{
    trackID = ID;

    lcd = uid;
    keypad = kpd;

    pitchShiftView.init(ID, driver, lcd, keypad);
    waveshaperView.init(ID, driver, lcd, keypad);
    filterView.init(ID, driver, lcd, keypad);
    delayView.init(ID, driver, lcd, keypad);
    reverbView.init(ID, driver, lcd, keypad);

    selectedEffectIndex = 0;
    isOpen = false;
    isPainted = false;
}

void TrackView::tick()
{
    pitchShiftView.tick();
    waveshaperView.tick();
    filterView.tick();
    delayView.tick();
    reverbView.tick();

    if(isOpen)
        repaint();
}

void TrackView::repaint()
{
    if(!isPainted)
    {
        // Track label box and text 
        Rectangle trackLabelRect(10, 10, StyleSheet::Tracks::displayWidth - 20, 50);  
        lcd->DrawRect(trackLabelRect, StyleSheet::Tracks::borderColor);
        lcd->WriteString(("Track " + std::to_string(trackID)).c_str(), 20, 15, StyleSheet::Tracks::largerFont, COLOR_CYAN);

        // Draw the effects label box 
        Rectangle effectsLabelRect(10, 65, 150, 30);
        lcd->DrawRect(effectsLabelRect, StyleSheet::Tracks::borderColor);
        lcd->WriteString("Effects", 50, 70, Font_11x18, COLOR_CYAN);

        // Top position for effect boxes
        int effectsYStart = 96; 

        // Effects and their description lines
        const char* effects[] = {"Delay", "Reverb", "Waveshaper", "Pitch Shift", "Filter"};

        const char* descriptions[][8]= {
            {
                "Delay is like an",
                "echo. When you",
                "shout into a big",
                "room or a mountain,",
                "your voice bounces",
                "back to you after a",
                "little while."
            },
            {
                "Reverb sounds like",
                "the noise is all",
                "around you, ",
                "bouncing off walls",
                "quickly. It's like",
                "the sound you hear",
                "when you clap in a",
                "large hall."
            },
            {
                "Waveshaper changes",
                "the sound by making",
                "it more fuzzy or",
                " buzzy, adding",
                "sharp zigzags to a",
                "smooth, curvy line."
            },
            {
                "Pitch Shift is like",
                "changing the notes",
                "on a piano while",
                "you're still",
                "pressing the same",
                "key, making sounds",
                "higher or lower."
            },
            {
                "Filter lets through",
                "only the parts of",
                "sound you want to",
                "hear, like using a",
                "sieve to separate",
                "larger things from",
                "smaller things."
            }
        };
        int effectsCount = sizeof(effects) / sizeof(effects[0]);

        // Calc height for effect boxes 
        int effectBoxHeight = (StyleSheet::Tracks::displayHeight - effectsYStart - 10 - (effectsCount * 1)) / effectsCount; 

        // Description box same height as all effects boxes
        int descriptionBoxHeight = effectsCount * effectBoxHeight + (effectsCount - 1); 

        // Draw each effect box
        for (int i = 0; i < effectsCount; ++i) 
        {
            int effectTop = effectsYStart + i * (effectBoxHeight + 1); 
            uint16_t fillColor = (i == selectedEffectIndex) ? StyleSheet::Tracks::selectedEffectColor : StyleSheet::Tracks::effectBoxColor;
            lcd->FillRect(Rectangle(11, effectTop + 1, 148, effectBoxHeight - 2), fillColor);
            lcd->DrawRect(Rectangle(10, effectTop, 150, effectBoxHeight), StyleSheet::Tracks::borderColor);
            lcd->WriteString(effects[i], 20, effectTop + (effectBoxHeight - StyleSheet::Tracks::smallerFontHeight) / 2, StyleSheet::Tracks::smallerFont, StyleSheet::Tracks::text_color);
        }

        // Draw the description label box and the larger description box
        Rectangle descLabelRect(170, 65, StyleSheet::Tracks::displayWidth - 180, 30);
        lcd->DrawRect(descLabelRect, StyleSheet::Tracks::borderColor);
        lcd->WriteString("Description", 180, 70, Font_11x18, COLOR_CYAN);

        Rectangle descRect(170, effectsYStart, StyleSheet::Tracks::displayWidth - 180, descriptionBoxHeight);
        lcd->DrawRect(descRect, StyleSheet::Tracks::borderColor);

        // Calculate the number of lines for the selected effect's description
        int numDescriptionLines = sizeof(descriptions[selectedEffectIndex]) / sizeof(descriptions[selectedEffectIndex][0]);

        // Write each line within the description box for the selected effect
        int currentY = effectsYStart + 10;
        for (int i = 0; i < numDescriptionLines; i++) 
        {
            lcd->WriteString(descriptions[selectedEffectIndex][i], 175, currentY, StyleSheet::Tracks::smallerFont, StyleSheet::Tracks::text_color);
            currentY += StyleSheet::Tracks::smallerFontHeight + 2; // Adding a little space between lines for readability
        }

        isPainted = true;
    }
}

void TrackView::clear()
{

}