#include "TrackView.h"

void TrackView::init(int ID)
{
    // lcd driver pointer
    // keypad driver pointer

    trackID = ID;
}

void TrackView::tick()
{
    pitchShiftView.tick();
    waveshaperView.tick();
    filterView.tick();
    reverbView.tick();
    delayView.tick();
}

void TrackView::paint()
{

}