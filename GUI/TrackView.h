#ifndef TRACKVIEW_H
#define TRACKVIEW_H

#include "../Parameters/ParameterIDs.h"
#include "FX/PitchShiftView.h"
#include "FX/WaveshaperView.h"
#include "FX/FilterView.h"
#include "FX/ReverbView.h"
#include "FX/DelayView.h"

/********************************************//**
 *  Class name: TrackView
 *  Function: Track level GUI class
 ***********************************************/

class TrackView
{
public:

    void init(int ID, EncoderDriver* driver, UiDriver* uid, KeypadDriver* kpd);
    void tick();

    void repaint();
    void clear();

    void setIsOpen(bool state) { isOpen = state; }

private:

    int trackID;

    UiDriver* lcd;
    KeypadDriver* keypad;

    PitchShiftView pitchShiftView;
    WaveshaperView waveshaperView;
    FilterView filterView;
    ReverbView reverbView;
    DelayView delayView;

    bool isOpen;
    bool isPainted;
};

#endif