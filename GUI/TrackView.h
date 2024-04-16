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

    void init(int ID, EncoderDriver* driver);
    void tick();

    void repaint();
    void clear();

private:

    // lcd driver pointer
    // keypad driver pointer

    PitchShiftView pitchShiftView;
    WaveshaperView waveshaperView;
    FilterView filterView;
    ReverbView reverbView;
    DelayView delayView;

    bool isOpen;
    int trackID;
};

#endif