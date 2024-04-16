#include "DelayView.h"

void DelayView::init(int ID, EncoderDriver* driver, UiDriver* uid, KeypadDriver* kpd)
{
    trackID = ID;

    lcd = uid;
    keypad = kpd;

    amount.init(trackID + ParameterIDs::Delay::amount, driver, lcd);
    size.init(trackID + ParameterIDs::Delay::size, driver, lcd);
    feedback.init(trackID + ParameterIDs::Delay::feedback, driver, lcd);

    isOpen = false;
}

void DelayView::tick()
{
    amount.tick();
    size.tick();
    feedback.tick();
}

void DelayView::repaint()
{

}

void DelayView::clear()
{

}