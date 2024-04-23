#include "MixerView.h"

void MixerView::init(DaisySeed* seed, EncoderDriver* encoder, UiDriver* uid, KeypadDriver* kpd)
{
    lcd = uid;
    keypad = kpd;

    amp1.init(0, seed);
    amp2.init(1, seed);
    amp3.init(2, seed);
    amp4.init(3, seed);

    track1.init(ParameterIDs::Tracks::Track1, encoder, lcd, keypad);
    track2.init(ParameterIDs::Tracks::Track2, encoder, lcd, keypad);
    track3.init(ParameterIDs::Tracks::Track3, encoder, lcd, keypad);
    track4.init(ParameterIDs::Tracks::Track4, encoder, lcd, keypad);
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
    
}

void MixerView::clear()
{
    
}