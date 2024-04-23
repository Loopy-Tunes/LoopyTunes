#include "WaveshaperView.h"

void WaveshaperView::init(int ID, EncoderDriver* driver, UiDriver* uid, KeypadDriver* kpd)
{
    trackID = ID;

    lcd = uid;
    keypad = kpd;

    // init bypass
    amount.init(trackID + ParameterIDs::Waveshaper::amount, driver, lcd);
    funcControl.init(trackID + ParameterIDs::Waveshaper::funcControl, driver, lcd);
    mode.init(trackID + ParameterIDs::Waveshaper::mode, driver, lcd);

    isOpen = false;
}

void WaveshaperView::tick()
{
    amount.tick();
    funcControl.tick();
    mode.tick();

    if(isOpen)
        repaint();
}

void WaveshaperView::repaint()
{
    
}

void WaveshaperView::clear()
{

}