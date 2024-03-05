#include "PitchShift.h"

void PitchShift::init(DaisySeed* seed)
{
    for(size_t i = 0 ; i < BLOCKLENGTH ; i++)
    {
        buffer[L][i] = 0.0f;
        buffer[R][i] = 0.0f;
    }
    
    shifter.Init(seed->AudioSampleRate());

    //bypass.param.init(daisy::seed::D5, 1000, [this]{ setBypass(); }); // CHECK THIS
    amount.param.init(seed, 0, 1, LINEAR, ChannelIDs::ENCODER, [this] (float a) { amount.value = a; });
    semitones.init(seed, 0, 1, LINEAR, ChannelIDs::AMP2, [this] (int s) { shifter.SetTransposition(s); });
    timbre.init(seed, 0, 1, LINEAR, ChannelIDs::AMP3, [this] (u_int32_t t) { shifter.SetDelSize(t); });
    rand.init(seed, 0, 1, LINEAR, ChannelIDs::AMP4, [this] (float r) { shifter.SetFun(r); });

    // set default values 
    bypass.value = false;
}

void PitchShift::tick()
{
    //bypass.tick();
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

        buffer[L][i] = shifter.Process(buffer[L][i]);
        buffer[R][i] = shifter.Process(buffer[R][i]);

        input[L][i] = (input[L][i] * (1.f - amount.value)) + (buffer[L][i] * amount.value);
        input[R][i] = (input[R][i] * (1.f - amount.value)) + (buffer[R][i] * amount.value);
    }
}