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
    rand.init(seed, 0, 1, LINEAR, ChannelIDs::AMP4, [this] (float r) { shifter.SetFun(r); });

    // set default values 
    bypass.value = false;
    amount.param.setIsSelected(true);
    amount.value = 1;
    shifter.SetDelSize(2400);
}

void PitchShift::tick()
{
    //bypass.tick();
    semitones.tick();
    rand.tick();
}

void PitchShift::process(float* input[2], size_t size)
{
    if(bypass.value)
        return;

    for(size_t i = 0 ; i < size ; i++)
    {
        input[L][i] = shifter.Process(input[L][i]);
        input[R][i] = shifter.Process(input[R][i]);

        //input[L][i] = (input[L][i] * (1.f - amount.value)) + (buffer[L][i] * amount.value);
        //input[R][i] = (input[R][i] * (1.f - amount.value)) + (buffer[R][i] * amount.value);
    }
}