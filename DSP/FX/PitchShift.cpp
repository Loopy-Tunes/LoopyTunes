#include "PitchShifter.h"

void PitchShift::init(DaisySeed* seed)
{
    for(size_t i = 0 ; i < BLOCKLENGTH ; i++)
    {
        buffer[L][i] = 0.0f;
        buffer[R][i] = 0.0f;
    }
    
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

void PitchShift::process(float* input[2], size_t size)
{
    if(bypass.value)
        return;

    for(size_t i = 0 ; i < size ; i++)
    {
        buffer[L][i] = input[L][i];
        buffer[R][i] = input[R][i];

        shifter.Process(buffer[L][i]);
        shifter.Process(buffer[R][i]);

        input[L][i] = (input[L][i] * (1.f - amount.value)) + (buffer[L][i] * amount.value);
        input[R][i] = (input[R][i] * (1.f - amount.value)) + (buffer[R][i] * amount.value);
    }
}