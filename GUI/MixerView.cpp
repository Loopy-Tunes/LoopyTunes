#include "MixerView.h"

void MixerView::init(DaisySeed* seed, EncoderDriver* encoder, KeypadDriver* kpd)
{
    //keypad = kpd;

    amp1.init(0, seed);
    amp2.init(1, seed);
    amp3.init(2, seed);
    amp4.init(3, seed);

    selectedChannel = 0;

    track1.init(1, encoder, keypad);
    track2.init(2, encoder, keypad);
    track3.init(3, encoder, keypad);
    track4.init(4, encoder, keypad);
}

void MixerView::tick()
{
    amp1.tick();
    amp2.tick();
    amp3.tick();
    amp4.tick();

    track1.tick();
    track2.tick();
    track3.tick();
    track4.tick();

    if(isOpen)
        repaint();
}

void MixerView::repaint()
{
    if(!isPainted)
    {
        // Draw the header frames and texts only for the first channel to avoid redundancy
        // Screen border
        lcd.DrawRect(Rectangle(StyleSheet::Mixer::frameThickness, StyleSheet::Mixer::frameThickness, StyleSheet::Mixer::screenWidth - (2 * StyleSheet::Mixer::frameThickness), StyleSheet::Mixer::screenHeight - (2 * StyleSheet::Mixer::frameThickness)), StyleSheet::Mixer::frameColor);
        // "Tempo 120" frame and text
        const int tempoBoxWidth = 75; 
        lcd.DrawRect(Rectangle(2, 2, tempoBoxWidth, 30), StyleSheet::Mixer::frameColor);
        lcd.WriteString("Tempo 120", 10, 15, Font_7x10, StyleSheet::Mixer::frameColor);
            
        // "Main Mixer" 
        const int mainMixerTextY = 7; 
        int mainMixerTextX = (StyleSheet::Mixer::screenWidth / 2) - (4 * 19); 
        lcd.WriteString("Main Mixer", mainMixerTextX, mainMixerTextY, Font_16x26, StyleSheet::Mixer::frameColor);

        // "Waveform" frame and text
        const int waveformBoxWidth = 72; 
        int waveformTextX = StyleSheet::Mixer::screenWidth - waveformBoxWidth; 
        lcd.DrawRect(Rectangle(waveformTextX, 2, waveformBoxWidth-2, 30), StyleSheet::Mixer::frameColor);
        lcd.WriteString("Waveform", waveformTextX + 5, 15, Font_7x10, StyleSheet::Mixer::frameColor);

        isPainted = true;
    }

    // Fader drawing code for all channels
    for(int i = 0 ; i < 4 ; i++)
    {
        if(i == selectedChannel)
            ampSliders[i].repaint(i, true);
        else
            ampSliders[i].repaint(i, false);
    }
}

void MixerView::clear()
{
    
}