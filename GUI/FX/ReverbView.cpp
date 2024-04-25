#include "ReverbView.h"

void ReverbView::init(int ID, EncoderDriver* driver, UiDriver* uid, KeypadDriver* kpd)
{
    trackID = ID;

    lcd = uid;
    keypad = kpd;

    bypass.init(driver, driver->getBypassCallback(bypassIndexes[ID-1]));
    amount.init(trackID + ParameterIDs::Reverb::amount, driver, lcd);
    size.init(trackID + ParameterIDs::Reverb::size, driver, lcd);

    isOpen = false;
}

void ReverbView::tick()
{
    amount.tick();
    size.tick();

    if(isOpen)
        repaint();
}

void ReverbView::repaint()
{
    if(isPainted)
        return;


    isPainted = false;
}

void ReverbView::clear()
{

}