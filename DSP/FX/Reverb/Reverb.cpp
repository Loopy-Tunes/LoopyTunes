#include "Reverb.h"

void Reverb::init(DaisySeed* seed)
{
    mode.init(seed, 0, 1, LINEAR, ChannelIDs::ENCODER, [this] (float m) { model.setmode(m); });
    size.init(seed, 0, 1, LINEAR, ChannelIDs::ENCODER, [this] (float s) { model.setroomsize(s); });
    damp.init(seed, 0, 1, LINEAR, ChannelIDs::ENCODER, [this] (float d) { model.setdamp(d); });
    wet.init(seed, 0, 1, LINEAR, ChannelIDs::ENCODER, [this] (float w) { model.setwet(w); });
    dry.init(seed, 0, 1, LINEAR, ChannelIDs::ENCODER, [this] (float d) { model.setdry(d); });
    width.init(seed, 0, 1, LINEAR, ChannelIDs::ENCODER, [this] (float w) { model.setwidth(w); });
}

void Reverb::process()
{

}

void Reverb::processReplacing()
{

}

void Reverb::suspend()
{

}

void Reverb::resume()
{

}