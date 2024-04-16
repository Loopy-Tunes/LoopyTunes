#include "ReverbView.h"

void ReverbView::init(int ID, EncoderDriver* driver, UiDriver* uid, KeypadDriver* kpd)
{
    trackID = ID;

    lcd = uid;
    keypad = kpd;

    // init bypass
    amount.init(trackID + ParameterIDs::Reverb::amount, driver, lcd);
    size.init(trackID + ParameterIDs::Reverb::size, driver, lcd);

    isOpen = false;
}

void ReverbView::tick()
{
    amount.tick();
    size.tick();
}

void ReverbView::repaint()
{
    if(!isOpen)
        return;
}

void ReverbView::clear()
{

}