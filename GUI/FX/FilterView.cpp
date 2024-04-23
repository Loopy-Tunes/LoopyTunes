#include "FilterView.h"

void FilterView::init(int ID, EncoderDriver* driver, UiDriver* uid, KeypadDriver* kpd)
{
    trackID = ID;

    lcd = uid;
    keypad = kpd;

    // init bypass
    mode.init(trackID + ParameterIDs::Filter::mode, driver, lcd);
    frequency.init(trackID + ParameterIDs::Filter::frequency, driver, lcd);
    resonance.init(trackID + ParameterIDs::Filter::resonance, driver, lcd);

    isOpen = false;
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
   
}

void FilterView::clear()
{

}