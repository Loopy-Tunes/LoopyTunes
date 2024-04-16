#include "DelayView.h"

void DelayView::init(int ID, EncoderDriver* driver)
{
    trackID = ID;

    amount.init(trackID + ParameterIDs::Delay::amount, driver);
    size.init(trackID + ParameterIDs::Delay::size, driver);
    feedback.init(trackID + ParameterIDs::Delay::feedback, driver);

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