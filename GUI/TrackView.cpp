#include "TrackView.h"

void TrackView::init(int ID, EncoderDriver* driver)
{
    // lcd driver pointer
    // keypad driver pointer

    trackID = ID;

    pitchShiftView.init(ID + ParameterIDs::PitchShifter::effect, driver);
    waveshaperView.init(ID + ParameterIDs::Waveshaper::effect, driver);
    filterView.init(ID + ParameterIDs::Filter::effect, driver);
    reverbView.init(ID + ParameterIDs::Reverb::effect, driver);
    delayView.init(ID + ParameterIDs::Delay::effect, driver);
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