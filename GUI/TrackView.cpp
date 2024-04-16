#include "TrackView.h"

void TrackView::init(int ID, EncoderDriver* driver)
{
    // lcd driver pointer
    // keypad driver pointer

    trackID = ID;

    pitchShiftView.init(ID, driver);
    waveshaperView.init(ID, driver);
    filterView.init(ID, driver);
    reverbView.init(ID, driver);
    delayView.init(ID, driver);
}

void TrackView::tick()
{
    pitchShiftView.tick();
    waveshaperView.tick();
    filterView.tick();
    reverbView.tick();
    delayView.tick();
}

void TrackView::repaint()
{

}

void TrackView::clear()
{

}