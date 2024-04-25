#include "FilterView.h"

void FilterView::init(int ID, EncoderDriver* driver, UiDriver* uid, KeypadDriver* kpd)
{
    trackID = ID;

    lcd = uid;
    keypad = kpd;

    bypass.init(driver, driver->getBypassCallback(bypassIndexes[ID-1]));
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
   if(isPainted)
        return;


    isPainted = false;
}

void FilterView::clear()
{

}