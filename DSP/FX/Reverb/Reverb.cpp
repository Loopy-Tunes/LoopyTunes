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

void Reverb::tick()
{
    mode.tick();
    size.tick();
    damp.tick();
    wet.tick();
    dry.tick();
    width.tick();
}

void Reverb::processBlock(float* input[2], long size)
{
    // need to add functionality so that it takes data from the read pointer
    if(bypass.value)
        return;
    
    model.processmix(input[L], input[R], input[L], input[R], size, 0);
}

void Reverb::processBlockReplacing(float* input[2], float* output[2], long size, size_t readPos)
{
    if(bypass.value)
        return;

    model.processreplace(input[L], input[R], output[L], output[R], size, 0);
}

void Reverb::suspend()
{
    model.mute();
}

void Reverb::resume()
{
    model.mute();
}