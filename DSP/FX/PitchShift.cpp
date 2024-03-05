#include "PitchShifter.h"

void PitchShift::init(DaisySeed* seed)
{
    shifter.init(seed->AudioSampleRate);

    //bypass.param.init(daisy::seed::D5, 1000, [this]{ setBypass(); }); // CHECK THIS
    semitones.param.init(seed, 0, 1, LINEAR, ChannelIDs::ENCODER, [this] (int s) { shifter.SetTransposition(s); });
    timbre.param.init(seed, 0, 1, LINEAR, ChannelIDs::ENCODER, [this] (u_int32_t t) { shifter.setDelSize(s); });
    rand.param.init(seed, 0, 1, LINEAR, ChannelIDs::ENCODER, [this], (float r) { shifter.setFun(r); });
}

void PitchShift::tick()
{
    bypass.tick();
    semitones.tick();
    timbre.tick();
    rand.tick();
}

void PitchShift::process(float* input[2])
{
    if(bypass.value)
        return;

    
}