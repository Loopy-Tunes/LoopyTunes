#include "Reverb.h"

void Reverb::init(DaisySeed* seed)
{
    amount.init(seed, 0, 1, LINEAR, ChannelIDs::AMP3, [this] (float a) { setAmount(a); });
    mode.init(seed, 0, 1, LINEAR, ChannelIDs::ENCODER, [this] (float m) { model.setmode(m); });
    size.init(seed, 0, 1, LINEAR, ChannelIDs::AMP2, [this] (float s) { model.setroomsize(s); });
    //damp.init(seed, 0, 1, LINEAR, ChannelIDs::ENCODER, [this] (float d) { model.setdamp(d); });
    //width.init(seed, 0, 1, LINEAR, ChannelIDs::ENCODER, [this] (float w) { model.setwidth(w); });

    // set default values
    model.setdamp(1.f);
    model.setroomsize(0.5);
    model.setdamp(0.5);
    model.setwidth(0.5);
}

void Reverb::tick()
{
    amount.tick();
    mode.tick();
    size.tick();
    //damp.tick();
    //width.tick();
}

void Reverb::setAmount(float mix)
{
    float wet = mix;
    float dry = 1.f - mix;

    model.setwet(wet);
    model.setdry(dry);
}

void Reverb::processBlock(float* input[2], long size)
{
    //if(bypass.value)
        //return;
    
    model.processreplace(input[L], input[R], output[L], output[R], size, 0);

    for(long i = 0 ; i < size ; i++)
    {
        input[L][i] = output[L][i];
        input[R][i] = output[R][i];
    }
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