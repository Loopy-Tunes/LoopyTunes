#include "Reverb.h"

void Reverb::init(EncoderDriver* driver, int trackID)
{
    amount.param.init(0, 1, 0.05, ParameterIDs::Reverb::amount, trackID, [this] (float a) { setAmount(a); });
    mode.param.init(0, 1, 0.25, ParameterIDs::Reverb::mode, trackID, [this] (float m) { model.setmode(m); });
    size.param.init(0, 1, 0.05, ParameterIDs::Reverb::size, trackID, [this] (float s) { model.setroomsize(s); });
    damp.param.init(0, 1, 0.05, ParameterIDs::Reverb::damp, trackID, [this] (float d) { model.setdamp(d); });
    width.param.init(0, 1, 0.05, ParameterIDs::Reverb::width, trackID, [this] (float w) { model.setwidth(w); });

    driver->addBypassCallback([this] { setBypass(); });
    driver->addParameter(&amount.param);
    driver->addParameter(&mode.param);
    driver->addParameter(&size.param);
    driver->addParameter(&damp.param);
    driver->addParameter(&width.param);

    model.setdry(1);
    setDefaultValues();
}

void Reverb::setDefaultValues()
{
    isBypass = true;
    setAmount(reverbDefs.amount);
    model.setmode(reverbDefs.mode);
    model.setroomsize(reverbDefs.size);
    model.setdamp(reverbDefs.damp);
    model.setwidth(reverbDefs.width);
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
    if(isBypass)
        return;
    
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