#include "MixerView.h"

void MixerView::init(DaisySeed* seed, EncoderDriver* driver)
{
    amp1.init(0, seed);
    amp2.init(1, seed);
    amp3.init(2, seed);
    amp4.init(3, seed);

    track1.init(ParameterIDs::Tracks::Track1, driver);
    track2.init(ParameterIDs::Tracks::Track2, driver);
    track3.init(ParameterIDs::Tracks::Track3, driver);
    track4.init(ParameterIDs::Tracks::Track4, driver);
}

void MixerView::tick()
{
    amp1.tick();
    amp2.tick();
    amp3.tick();
    amp4.tick();

    track1.tick();
    track2.tick();
    track3.tick();
    track4.tick();
}

void MixerView::repaint()
{

}

void MixerView::clear()
{
    
}