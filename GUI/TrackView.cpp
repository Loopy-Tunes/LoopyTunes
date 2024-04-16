#include "TrackView.h"

void TrackView::init(int ID, EncoderDriver* driver, UiDriver* uid, KeypadDriver* kpd)
{
    trackID = ID;

    lcd = uid;
    keypad = kpd;

    pitchShiftView.init(ID, driver, lcd, keypad);
    waveshaperView.init(ID, driver, lcd, keypad);
    filterView.init(ID, driver, lcd, keypad);
    reverbView.init(ID, driver, lcd, keypad);
    delayView.init(ID, driver, lcd, keypad);
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
    if(!isOpen)
        return;
}

void TrackView::clear()
{

}