#include "PitchShiftView.h"

void PitchShiftView::init(int ID, EncoderDriver* driver, UiDriver* uid, KeypadDriver* kpd)
{
    trackID = ID;

    lcd = uid;
    keypad = kpd;

    bypass.init(driver, driver->getBypassCallback(bypassIndexes(ID - 1)));
    amount.init(trackID + ParameterIDs::PitchShifter::amount, driver, lcd);
    semitones.init(trackID + ParameterIDs::PitchShifter::semitones, driver, lcd);

    isOpen = false;
}

void PitchShiftView::tick()
{
    amount.tick();
    semitones.tick();

    if(isOpen)
        repaint();
}

void PitchShiftView::repaint()
{

}

void PitchShiftView::clear()
{

}