#include "FilterView.h"

void FilterView::init(int ID, EncoderDriver* driver)
{
    trackID = ID;

    mode.init(trackID + ParameterIDs::Filter::mode, driver);
    frequency.init(trackID + ParameterIDs::Filter::frequency, driver);
    resonance.init(trackID + ParameterIDs::Filter::resonance, driver);

    isOpen = false;
}

void FilterView::tick()
{
    mode.tick();
    frequency.tick();
    resonance.tick();
}

void FilterView::repaint()
{

}

void FilterView::clear()
{

}