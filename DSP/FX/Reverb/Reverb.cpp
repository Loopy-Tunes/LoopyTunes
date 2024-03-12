#include "Reverb.h"

void Reverb::init(DaisySeed* seed)
{
    amount.init(seed, 0, 1, LINEAR, ChannelIDs::AMP3, [this] (float a) { model.setwet(a); });
    //mode.init(seed, 0, 1, LINEAR, ChannelIDs::ENCODER, [this] (float m) { model.setmode(m); });
    size.init(seed, 0, 1, LINEAR, ChannelIDs::AMP2, [this] (float s) { model.setroomsize(s); });
    damp.init(seed, 0, 1, LINEAR, ChannelIDs::AMP4, [this] (float d) { model.setdamp(d); });
    //width.init(seed, 0, 1, LINEAR, ChannelIDs::ENCODER, [this] (float w) { model.setwidth(w); });

    model.setdry(0.8);
    //setDefaultValues();
}

void Reverb::setDefaultValues()
{
    bypass.value = reverbDefs.bypass;
    setAmount(reverbDefs.amount);
    model.setmode(reverbDefs.mode);
    model.setroomsize(reverbDefs.size);
    model.setdamp(reverbDefs.damp);
    model.setwidth(reverbDefs.width);
}

void Reverb::tick()
{
    amount.tick();
    //mode.tick();
    size.tick();
    damp.tick();
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

void Reverb::suspend()
{
    model.mute();
}

void Reverb::resume()
{
    model.mute();
}