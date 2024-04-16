#include "WaveshaperView.h"

void WaveshaperView::init(int ID, EncoderDriver* driver)
{
    trackID = ID;

    amount.init(trackID + ParameterIDs::Waveshaper::amount, driver);
    funcControl.init(trackID + ParameterIDs::Waveshaper::funcControl, driver);
    mode.init(trackID + ParameterIDs::Waveshaper::mode, driver);

    isOpen = false;
}

void WaveshaperView::tick()
{
    amount.tick();
    funcControl.tick();
    mode.tick();
}

void WaveshaperView::repaint()
{

}

void WaveshaperView::clear()
{

}