#include "ReverbView.h"

void ReverbView::init(int ID, EncoderDriver* driver)
{
    trackID = ID;

    amount.init(trackID + ParameterIDs::Reverb::amount, driver);
    size.init(trackID + ParameterIDs::Reverb::size, driver);

    isOpen = false;
}

void ReverbView::tick()
{

}

void ReverbView::repaint()
{

}

void ReverbView::clear()
{

}