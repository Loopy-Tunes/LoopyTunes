#include "PitchShiftView.h"

void PitchShiftView::init(int ID, EncoderDriver* driver, UiDriver* uid, KeypadDriver* kpd)
{
    trackID = ID;

    lcd = uid;
    keypad = kpd;

    // init bypass
    amount.init(trackID + ParameterIDs::PitchShifter::amount, driver, lcd);
    semitones.init(trackID + ParameterIDs::PitchShifter::semitones, driver, lcd);

    isOpen = false;
}

void PitchShiftView::tick()
{
    amount.tick();
    semitones.tick();
}

void PitchShiftView::repaint()
{
    if(!isOpen)
        return;
}

void PitchShiftView::clear()
{

}