#include "MixerView.h"

void MixerView::init()
{
    track1.init(ParameterIDs::Tracks::Track1);
    track2.init(ParameterIDs::Tracks::Track2);
    track3.init(ParameterIDs::Tracks::Track3);
    track4.init(ParameterIDs::Tracks::Track4);
}

void MixerView::tick()
{
    track1.tick();
    track2.tick();
    track3.tick();
    track4.tick();
}

void MixerView::paint()
{

}

void MixerView::updateAmplitudes()
{

}