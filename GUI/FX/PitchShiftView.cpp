#include "PitchShiftView.h"

void PitchShiftView::init(int ID, EncoderDriver* driver)
{
    trackID = ID;

    amount.init(trackID + ParameterIDs::PitchShifter::amount, driver);
    semitones.init(trackID + ParameterIDs::PitchShifter::semitones, driver);

    isOpen = false;
}

void PitchShiftView::tick()
{
    amount.tick();
    semitones.tick();
}

void PitchShiftView::repaint()
{

}

void PitchShiftView::clear()
{

}